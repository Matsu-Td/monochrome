
/**
 * @file mapchips.cpp
 * @brief マップデータ、JSONファイル読み込み
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#define	_CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MapChips.h"
#include "ResourceServer.h"
#include "Game.h"

#include "picojson/picojson.h"

MapChips::MapChips(std::string filePath, std::string tiledFileName)
{
	// jsonデータからマップデータをロードする
	TiledJsonLoad(filePath, tiledFileName + ".json");

	_mh[0] = MV1LoadModel("res/model/kenban.siro.2.mv1");
	_mh[1] = MV1LoadModel("res/model/kenban.siro.3.mv1");
	MV1SetScale(_mh[0], VGet(155.0f, 155.0f, 155.0f));
	MV1SetScale(_mh[1], VGet(155.0f, 155.0f, 155.0f));
}

MapChips::~MapChips()
{
	delete[] _mapData;
}

// 文字列のファイルをロードする
std::string MapChips::StringFileLoad(std::string strFileName)
{
	FILE* fp;
	fp = fopen(strFileName.c_str(), "rb");
	if (fp == NULL)
	{
		return "";
	}
	// ファイルのサイズを取得
	fseek(fp, 0, SEEK_END); int size = ftell(fp); fseek(fp, 0, SEEK_SET);
	
	char* p;
	p = new char[size + 1];
	fread(p, 1, size, fp);

	fclose(fp);
	p[size] = '\0';

	// 読み込んだデータをstringにする
	std::string s = (char*)p;

	delete[] p;

	return s;
}

// Tiled-jsonデータロード
int		MapChips::TiledJsonLoad(std::string filePath, std::string strFileName)
{
	// ファイルを開いてstringを取得する
	std::string strJson = StringFileLoad(filePath + strFileName);
	if (strJson == "")
	{
		return 0;
	}

	// 読み込んだstringをjsonオブジェクト化する
	picojson::value json;
	picojson::parse(json, strJson);
	picojson::object jsRoot = json.get<picojson::object>();

	// パラメータをjsonから取得
	_mapSizeX = (int)jsRoot["width"].get<double>();
	_mapSizeZ = (int)jsRoot["height"].get<double>();

	// タイルセット取得(1つのみ対応)
	picojson::array aTileSets = jsRoot["tilesets"].get<picojson::array>();
	picojson::object jsTile = aTileSets[0].get<picojson::object>();
	_blockSizeX = (int)jsRoot["tilewidth"].get<double>();
	_blockSizeZ = (int)jsRoot["tileheight"].get<double>();

	// レイヤー情報の取得
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();
	// マップの"tilelayer"レイヤー数を数える
	int layer;
	layer = 0;
	for (int i = 0; i < aLayers.size(); i++)
	{
		picojson::object jsLayer = aLayers[i].get<picojson::object>();	
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			layer++;
		}
	}
	_mapSizeLayer = layer;

	// レイヤー内データの取得
	_mapData = new int[(int)(_mapSizeLayer * _mapSizeX * _mapSizeZ)];
	layer = 0;
	for (int i = 0; i < aLayers.size(); i++)
	{
		picojson::object jsLayer = aLayers[i].get<picojson::object>();
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			picojson::array aData = jsLayer["data"].get<picojson::array>();	
			for (int y = 0; y < _mapSizeZ; y++)
			{
				for (int x = 0; x < _mapSizeX; x++)
				{
					int layerstart = _mapSizeX * _mapSizeZ * layer;
					int index = y * _mapSizeX + x;
					_mapData[layerstart + index]= (int)aData[index].get<double>();
				}
			}
			layer++;
		}
	}

	return 1;
}

void MapChips::Draw(Game& g)
{
	switch (g._gStageNo) {
	case 0: case 1: case 2: case 5: case 6:
		MV1SetRotationXYZ(_mh[0], VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
		MV1SetRotationXYZ(_mh[1], VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f)); break;
	case 3: case 4:
		MV1SetRotationXYZ(_mh[0], VGet(0.0f, 90.0f * DX_PI_F / 90.0f, 0.0f));
		MV1SetRotationXYZ(_mh[1], VGet(0.0f, 90.0f * DX_PI_F / 90.0f, 0.0f)); break;
	}
	
	int layer;
	// ステージ3Dモデル描画
	for (layer = 0; layer < _mapSizeLayer; ++layer){
		for (int i = 0; i < _mapSizeZ; ++i) {
			for (int j = 0; j < _mapSizeX; ++j) {
				int layerstart = _mapSizeX * _mapSizeZ * layer;
				int index = i * _mapSizeX + j;
				// 道ではないところは描画しない
				if (_mapData[layerstart + index] == 0) { continue; }
				MV1SetPosition(_mh[_mapData[layerstart + index] % 2], VGet(static_cast<float>(j) * _blockSizeX, 0.0f, static_cast<float>(i) * _blockSizeZ));
				MV1DrawModel(_mh[_mapData[layerstart + index] % 2]);
			}
		}
	}
	// ゴール発生時、ゴール下の鍵盤も表示させる
	if (g._gHasKyuri == true) {
		switch (g._gStageNo) {
		case GAME::STAGENO::TUTORIAL:
			MV1SetPosition(_mh[1], VGet(8.0f * _blockSizeX, 0.0f, 7.0f * _blockSizeZ));
			MV1DrawModel(_mh[1]);
			break;
		case GAME::STAGENO::ST1_1:
			MV1SetPosition(_mh[1], VGet(2.0f * _blockSizeX, 0.0f, 5.0f * _blockSizeZ));
			MV1DrawModel(_mh[1]);
			break;
		case GAME::STAGENO::ST1_2:
			MV1SetPosition(_mh[0], VGet(0.0f * _blockSizeX, 0.0f, 4.0f * _blockSizeZ));
			MV1DrawModel(_mh[0]);
			break;
		case GAME::STAGENO::ST1_3:
			MV1SetPosition(_mh[0], VGet(2.0f * _blockSizeX, 0.0f, 0.0f * _blockSizeZ));
			MV1DrawModel(_mh[0]);
			break;
		case GAME::STAGENO::ST2_1:
			MV1SetPosition(_mh[1], VGet(1.0f * _blockSizeX, 0.0f, 4.0f * _blockSizeZ));
			MV1DrawModel(_mh[1]);
			break;
		case GAME::STAGENO::ST2_2:
			MV1SetPosition(_mh[1], VGet(0.0f * _blockSizeX, 0.0f, 1.0f * _blockSizeZ));
			MV1DrawModel(_mh[1]);
			break;
		case GAME::STAGENO::ST2_3:
			MV1SetPosition(_mh[1], VGet(3.0f * _blockSizeX, 0.0f, 8.0f * _blockSizeZ));
			MV1DrawModel(_mh[1]);
			break;
		}
	}
}