
/**
 * @file EnemyD.cpp
 * @brief 敵D(フライパン)の移動処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"

EnemyD::EnemyD(Game& g)
{
	_mh = MV1LoadModel("res/model/flypan.mv1");

	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);        
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex); 
	Init(g);
}

EnemyD::~EnemyD()
{
}

void EnemyD::Init(Game& g)
{
	// 初期位置&速さ
	switch (g._gStageNo) {
	case GAME::STAGENO::ST2_1:
		_x = 7; _z = 6; _spd = 1; break;
	case GAME::STAGENO::ST2_2:
		_x = 7; _z = 1; _spd = 3; break;
	case GAME::STAGENO::ST2_3:
		_x = 7; _z = 5; _spd = 3; break;
	}
	_r = 40;
	_movx = 0;
	_movz = 0;
	_nowx = _x * BLOCKSIZE;   //ドット移動にする
	_nowz = _z * BLOCKSIZE;   //ドット移動にする
	_nowy = 90;
	_root = 1;
	_direction = 2;
	// 再生時間の初期化
	_playTime = 0.0f;
}

void EnemyD::Process(Game& g)
{
	EnemyBase::Process(g);

	// 位置管理(ブロック番号)
	if (_nowx % BLOCKSIZE == 0 && _nowz % BLOCKSIZE == 0) {
		_x = _nowx / BLOCKSIZE;
		_z = _nowz / BLOCKSIZE;
	}

	switch (g._gStageNo) {
	case GAME::STAGENO::ST2_1:   // ステージ2-1
		//キュウリ君を捕まえる前の移動ルート
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(-1, 0, -_spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, 1, 0, _spd, 3, 0, g); break;
			case 3:
				MoveRoot(1, 0, _spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, 1, 0, _spd, 5, 0, g); break;
			case 5:
				MoveRoot(1, 0, _spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, 0, -_spd, 7, 11, g); break;
			case 7:
				MoveRoot(1, 0, _spd, 0, 8, 0, g); break;
			case 8:
				MoveRoot(0, -1, 0, -_spd, 1, 0, g); break;
			}
		}
		//キュウリ君を捕まえた後の移動ルート
		if (g._gHasKyuri == true) {
			switch (_root) {
			case 9:                        //初期位置へ移動
				MoveRoot(0, 0, 0, -_spd, 10, 9, g); break;
			case 10:
				MoveRoot(0, 1, 0, _spd, 11, 0, g); break;
			case 11:
				MoveRoot(-1, 0, -_spd, 0, 12, 0, g); break;
			case 12:
				MoveRoot(0, -1, 0, -_spd, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, _spd, 0, 10, 9, g); break;
			default:
				//ルート切替時、中途半端な座標にいた場合は位置を微調整して次のルートに移るようにする(誤動作防止)
				if (_nowz % BLOCKSIZE != 0) {       // 現在位置座標微調整（Z座標）
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {  // 現在位置座標微調整（X座標）
					if (_x < 5) {
						_nowx += _spd;
						_direction = CHARA::STATE::RIGHT_DOWN;
					}
					else {
						_nowx -= _spd;
						_direction = CHARA::STATE::LEFT_UP;
					}
				}
				else if (_x == 5) {                
					_root = 9;
				}
				else if (_x < 5) {
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				else {
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST2_2:   // ステージ2-2
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(-1, 0, -_spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, 1, 0, _spd, 3, 0, g); break;
			case 3:
				MoveRoot(1, 0, _spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, -1, 0, -_spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 5:                   
				MoveRoot(0, 0, _spd, 0, 6, 2, g); break;
			case 6:
				MoveRoot(0, 1, 0, _spd, 7, 0, g); break;
			case 7:
				MoveRoot(-1, 0, -_spd, 0, 8, 0, g); break;
			case 8:
				MoveRoot(1, 0, _spd, 0, 9, 0, g); break;
			case 9:
				MoveRoot(0, -1, 0, -_spd, 6, 0, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {   
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {  
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;

				}
				else if (_z == 1) {                 
					_root = 5;
				}
				else {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				break;
			}
		}
		break;
	case GAME::STAGENO::ST2_3:  // ステージ2-3
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, -_spd, 0, 2, 13, g); break;
			case 2:
				MoveRoot(0, 0, 0, -_spd, 3, 11, g); break;
			case 3:
				MoveRoot(1, 0, _spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, 0, 0, _spd, 1, 8, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 5:                   
				MoveRoot(0, 0, _spd, 0, 6, 6, g); break;
			case 6:
				MoveRoot(-1, 0, -_spd, 0, 7, 0, g); break;
			case 7:
				MoveRoot(0, 1, 0, _spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, _spd, 0, 9, 10, g); break;
			case 9:
				MoveRoot(0, 0, 0, -_spd, 6, 6, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {  
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				else if (_z == 3) {               
					_root = 5;
				}
				else {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				break;
			}
		}
		break;
	}

	_playTime += 0.7f;


	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}
}