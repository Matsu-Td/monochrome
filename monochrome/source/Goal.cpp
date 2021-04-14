
/**
 * @file Goal.cpp
 * @brief ゴール発生処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "Goal.h"
#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"
#include "ModeGame.h"
#include "ModeGameClear.h"

Goal::Goal(Game& g)
{
	_mh = MV1LoadModel("res/model/goal.mv1");

	Init(g);
}

Goal::~Goal()
{

}

void Goal::Init(Game& g)
{
	//ゴール各ステージ出現位置
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:   
		_x = 8; _z = 7; break;
	case GAME::STAGENO::ST1_1:   
		_x = 2; _z = 5; break;
	case GAME::STAGENO::ST1_2:          
		_x = 0; _z = 4; break;
	case GAME::STAGENO::ST1_3:     
		_x = 2; _z = 0; break;
	case GAME::STAGENO::ST2_1:          
		_x = 1; _z = 4; break;
	case GAME::STAGENO::ST2_2:      
		_x = 0; _z = 1; break;
	case GAME::STAGENO::ST2_3:    
		_x = 3; _z = 8; break;
	}

	_y = 90;
	_sx = 0.0f;
	_sy = 0.0f;
	_sz = 0.0f;
	_sizeUpSpd = 1.0f;
	_rotation = 0;
	_rotSpd = 2;
	_gameClearCnt = 0;
	_r = 30; 
}

void Goal::Process(Game& g)
{
	//当たり判定用
	_nowx = _x * BLOCKSIZE;
	_nowz = _z * BLOCKSIZE;

	// ゲームクリア処理
	if (_gameClearCnt > 0){
		_gameClearCnt--;
		if (_gameClearCnt == 0){
			StopSoundMem(g._se["nyuusyu"]);
			StopSoundMem(g._se["bgm08"]);
			PlaySoundMem(g._se["clear"], DX_PLAYTYPE_BACK);

			g._objServer.Del(this);
			ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");
			modeGame->_stopObjProcess = true;

			if (g._gStageNo != GAME::STAGENO::TUTORIAL) {  //チュートリアルでなければ
				ModeGameClear* modeGameClear = new ModeGameClear();
				g._serverMode->Add(modeGameClear, 1, "GameClear");
				switch (g._gStageNo) {
				case GAME::STAGENO::ST1_1:
					if (g._gMelodyTotal < 1) { g._gMelodyTotal = 1; } break;
				case GAME::STAGENO::ST1_2:
					if (g._gMelodyTotal < 2) { g._gMelodyTotal = 2; } break;
				case GAME::STAGENO::ST1_3:
					if (g._gMelodyTotal < 3) { g._gMelodyTotal = 3; } break;
				case GAME::STAGENO::ST2_1:
					if (g._gMelodyTotal < 4) { g._gMelodyTotal = 4; } break;
				case GAME::STAGENO::ST2_2:
					if (g._gMelodyTotal < 5) { g._gMelodyTotal = 5; } break;
				case GAME::STAGENO::ST2_3:
					if (g._gMelodyTotal < 6) { g._gMelodyTotal = 6; } break;
				}
			}
		}
		return;
	}
	
	if (g._gHasKyuri == true) {
		_rotation += _rotSpd;
		if (_sx <= MAX_SIZE && _sy <= MAX_SIZE && _sz <= MAX_SIZE) {
			_sx += _sizeUpSpd;
			_sy += _sizeUpSpd;
			_sz += _sizeUpSpd;
		}
	}

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			if (IsHit(*(*ite)) == true) {
				Damage(g);	
			}
		}
	}
}

void Goal::Draw(Game& g)
{
	MV1SetScale(_mh, VGet(_sx, _sy, _sz));
	if (g._gHasKyuri == true) {
		switch(g._gStageNo) {
		case GAME::STAGENO::TUTORIAL: 
		case GAME::STAGENO::ST1_2:
		case GAME::STAGENO::ST2_2:
			MV1SetRotationXYZ(_mh, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
			MV1SetRotationXYZ(_mh, VGet(_rotation / 10.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
			break;
		default:
			MV1SetRotationXYZ(_mh, VGet(0.0f, 0.0f, -_rotation / 10.0f));
			break;
		}
		MV1SetPosition(_mh, VGet(static_cast<float>(_x) * BLOCKSIZE, static_cast<float>(_y), static_cast<float>(_z) * BLOCKSIZE));
		MV1DrawModel(_mh);
	}
}

void Goal::Damage(Game& g)
{
	_gameClearCnt = 30;
}