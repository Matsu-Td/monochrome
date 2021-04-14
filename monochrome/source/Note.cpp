
/**
 * @file Note.cpp
 * @brief 音符獲得処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "Note.h"
#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"

Note::Note(Game& g)
{
	_mhNote[0] = MV1LoadModel("res/model/onpu_hachibu.mv1");
	_mhNote[1] = MV1LoadModel("res/model/onpu_shibu.mv1");
	
	Init();
}

Note::~Note()
{

}

void Note::Init()
{
	Pos.y = 90.0f;
	_sx = 0.0f;
	_sy = 0.0f;
	_sz = 0.0f;
	_rizeCnt = 420;
	_rotation = 0;
}

void Note::Process(Game& g)
{
	ObjectBase::Process(g);
	if (g._gHasKyuri == true) {
		--_rizeCnt;
		++_rotation;

		// 発生処理、サイズを0から元の大きさにする
		if (_sx <= MAX_SIZE && _sy <= MAX_SIZE && _sz <= MAX_SIZE) {
			_sx += 0.5f;
			_sy += 0.5f;
			_sz += 0.5f;
		}
		// 一定の高さまで上昇
		if (Pos.y <= 300.0f) {
			++Pos.y;
		}
		// 一定の高さを超えたら画面上部へ急加速
		else {
			Pos.y += 10.0f;
		}
		if (_rizeCnt == 0) {
			MV1DeleteModel(_mh);
			g._objServer.Del(this);
		}
	}
}

void Note::Draw(Game& g) 
{
	if (g._gHasKyuri == true) {
		MV1SetScale(_mhNote[g._gStageNo % 2], VGet(_sx, _sy, _sz));
		MV1SetPosition(_mhNote[g._gStageNo % 2], VGet(static_cast<float>(_x), Pos.y, static_cast<float>(_z)));
		MV1SetRotationXYZ(_mhNote[g._gStageNo % 2], VGet(0.0f, _rotation / 7.0f, 0.0f));
		MV1DrawModel(_mhNote[g._gStageNo % 2]);
	}
}