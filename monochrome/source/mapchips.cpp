
/**
 * @file mapchips.cpp
 * @brief �}�b�v�f�[�^�AJSON�t�@�C���ǂݍ���
 *
 * @date 2020-09-24
 * @author �������F
 */

#define	_CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MapChips.h"
#include "ResourceServer.h"
#include "Game.h"

#include "picojson/picojson.h"

MapChips::MapChips(std::string filePath, std::string tiledFileName)
{
	// json�f�[�^����}�b�v�f�[�^�����[�h����
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

// ������̃t�@�C�������[�h����
std::string MapChips::StringFileLoad(std::string strFileName)
{
	FILE* fp;
	fp = fopen(strFileName.c_str(), "rb");
	if (fp == NULL)
	{
		return "";
	}
	// �t�@�C���̃T�C�Y���擾
	fseek(fp, 0, SEEK_END); int size = ftell(fp); fseek(fp, 0, SEEK_SET);
	
	char* p;
	p = new char[size + 1];
	fread(p, 1, size, fp);

	fclose(fp);
	p[size] = '\0';

	// �ǂݍ��񂾃f�[�^��string�ɂ���
	std::string s = (char*)p;

	delete[] p;

	return s;
}

// Tiled-json�f�[�^���[�h
int		MapChips::TiledJsonLoad(std::string filePath, std::string strFileName)
{
	// �t�@�C�����J����string���擾����
	std::string strJson = StringFileLoad(filePath + strFileName);
	if (strJson == "")
	{
		return 0;
	}

	// �ǂݍ���string��json�I�u�W�F�N�g������
	picojson::value json;
	picojson::parse(json, strJson);
	picojson::object jsRoot = json.get<picojson::object>();

	// �p�����[�^��json����擾
	_mapSizeX = (int)jsRoot["width"].get<double>();
	_mapSizeZ = (int)jsRoot["height"].get<double>();

	// �^�C���Z�b�g�擾(1�̂ݑΉ�)
	picojson::array aTileSets = jsRoot["tilesets"].get<picojson::array>();
	picojson::object jsTile = aTileSets[0].get<picojson::object>();
	_blockSizeX = (int)jsRoot["tilewidth"].get<double>();
	_blockSizeZ = (int)jsRoot["tileheight"].get<double>();

	// ���C���[���̎擾
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();
	// �}�b�v��"tilelayer"���C���[���𐔂���
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

	// ���C���[���f�[�^�̎擾
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
	// �X�e�[�W3D���f���`��
	for (layer = 0; layer < _mapSizeLayer; ++layer){
		for (int i = 0; i < _mapSizeZ; ++i) {
			for (int j = 0; j < _mapSizeX; ++j) {
				int layerstart = _mapSizeX * _mapSizeZ * layer;
				int index = i * _mapSizeX + j;
				// ���ł͂Ȃ��Ƃ���͕`�悵�Ȃ�
				if (_mapData[layerstart + index] == 0) { continue; }
				MV1SetPosition(_mh[_mapData[layerstart + index] % 2], VGet(static_cast<float>(j) * _blockSizeX, 0.0f, static_cast<float>(i) * _blockSizeZ));
				MV1DrawModel(_mh[_mapData[layerstart + index] % 2]);
			}
		}
	}
	// �S�[���������A�S�[�����̌��Ղ��\��������
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