/** 
 * @file   EnemyA.cpp
 * @brief  エネミー(フライパンA)クラス
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"

int EnemyA::_enemyAPosX = 0;
int EnemyA::_enemyAPosZ = 0; 

EnemyA::EnemyA(Game& g)
{
	_mh = MV1LoadModel("res/model/flypan.mv1");
	
	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);            // 3Dモデルのアニメーションをアタッチする
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);  // アタッチしたアニメーションの総再生時間を取得する
	Init(g);
}

EnemyA::~EnemyA()
{
}

void EnemyA::Init(Game& g)
{
    // 初期位置&速さ
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:   
		_x = 1; _z = 7; _spd = 2; break;
	case GAME::STAGENO::ST1_1:     
		_x = 1; _z = 4; _spd = 3; break;
	case GAME::STAGENO::ST1_2:
		_x = 1; _z = 3; _spd = 1; break;
	case GAME::STAGENO::ST1_3:
		_x = 1; _z = 3; _spd = 2; break;
	case GAME::STAGENO::ST2_1:
		_x = 4; _z = 3; _spd = 3; break;
	case GAME::STAGENO::ST2_2:
		_x = 4; _z = 1; _spd = 2; break;
	case GAME::STAGENO::ST2_3:
		_x = 4; _z = 1; _spd = 2; break;
	}
	_r = 40;
	_movx = 0;
	_movz = 0;
	_nowx = _x * BLOCKSIZE;   //ドット移動にする
	_nowz = _z * BLOCKSIZE;   //ドット移動にする
	_nowy = 90;
	_root = 1;
	_direction = 2;

	_playTime = 0.0f;
}

void EnemyA::Process(Game& g)
{
	EnemyBase::Process(g);

	// 位置管理(ブロック番号)
	if (_nowx % BLOCKSIZE == 0 && _nowz % BLOCKSIZE == 0) {
		_x = _nowx / BLOCKSIZE;
		_z = _nowz / BLOCKSIZE;
	}
	
	// ステージ切替
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:   // チュートリアル
	//キュウリ君を捕まえる前の移動ルート
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, _spd, 0, 2, 11, g); break;
			case 2:
				MoveRoot(0, 0, 0, -_spd, 3, 8, g); break;
			case 3:
				MoveRoot(-1, 0, -_spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, -1, 0, -_spd, 5, 0, g); break;
			case 5:
				MoveRoot(0, 0, _spd, 0, 6, 5, g); break;
			case 6:
				MoveRoot(0, 0, 0, _spd, 7, 7, g); break;
			case 7:
				MoveRoot(0, 0, -_spd, 0, 8, 0, g); break;
			case 8:
				MoveRoot(0, 2, 0, _spd, 9, 12, g); break;
			case 9:
				MoveRoot(0, 0, -_spd, 0, 10, 12, g); break;
			case 10:
				MoveRoot(0, 1, 0, _spd, 11, 0, g); break;
			case 11:
				MoveRoot(0, 0, _spd, 0, 12, 12, g); break;
			case 12:
				MoveRoot(0, 0, 0, -_spd, 13, 6, g); break;
			case 13:
				MoveRoot(0, 0, _spd, 0, 14, 5, g); break;
			case 14:
				MoveRoot(0, 0, 0, _spd, 15, 8, g); break;
			case 15:
				MoveRoot(-1, 0, -_spd, 0, 16, 0, g); break;
			case 16:
				MoveRoot(0, 1, 0, _spd, 1, 0, g); break;
			}
		}

		// キュウリ君を捕まえた後の移動ルート
		if (g._gHasKyuri == true) {
			switch (_root) {
			case 17:                     // 初期位置へ移動する
				MoveRoot(0, 0, 0, _spd, 18, 14, g); break;
			case 18:
				MoveRoot(0, 0, _spd, 0, 19, 8, g); break;
			case 19:
				MoveRoot(0, 0, 0, -_spd, 20, 5, g); break;
			case 20:
				MoveRoot(0, 0, -_spd, 0, 21, 8, g); break;
			case 21:
				MoveRoot(0, 1, 0, _spd, 22, 0, g); break;
			case 22:
				MoveRoot(-1, 0, -_spd, 0, 18, 0, g); break;
			default:
				// ルート切替時、中途半端な座標にいた場合は位置を微調整して次のルートに移るようにする(誤動作防止)
				if (_nowz % BLOCKSIZE != 0) {       // 現在位置座標微調整（Z座標）
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else if (_nowx % BLOCKSIZE != 0) {  // 現在位置座標微調整（X座標）
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_x == 1) {
					_root = 17;
				}
				else {
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST1_1:   // ステージ1-1
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, _spd, 0, 2, 11, g); break;
			case 2:
				MoveRoot(0, 0, 0, _spd, 3, 0, g); break;
			case 3:
				MoveRoot(1, 0, _spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, -1, 0, -_spd, 5, 0, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, 0, _spd, 7, 13, g); break;
			case 7:
				MoveRoot(0, 1, 0, _spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, _spd, 0, 9, 13, g); break;
			case 9:
				MoveRoot(0, 0, 0, -_spd, 10, 9, g); break;
			case 10:
				MoveRoot(-1, 0, -_spd, 0, 11, 12, g); break;
			case 11:
				MoveRoot(0, 1, 0, _spd, 12, 0, g); break;
			case 12:
				MoveRoot(0, 0, -_spd, 0, 1, 13, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 13:              
				MoveRoot(0, 0, -_spd, 0, 14, 13, g); break;
			case 14:
				MoveRoot(0, 0, _spd, 0, 15, 12, g); break;
			case 15:
				MoveRoot(0, 0, 0, -_spd, 16, 9, g); break;
			case 16:
				MoveRoot(0, 0, -_spd, 0, 17, 10, g); break;
			case 17:
				MoveRoot(0, 0, 0, _spd, 18, 13, g); break;
			case 18:
				MoveRoot(0, 0, _spd, 0, 19, 11, g); break;
			case 19:
				MoveRoot(0, 0, 0, -_spd, 20, 8, g); break;
			case 20:
				MoveRoot(0, 0, -_spd, 0, 21, 10, g); break;
			case 21:
				MoveRoot(0, 0, 0, _spd, 14, 13, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {    
					if (_z < 4) {
						_nowz += _spd;
						_direction = CHARA::STATE::RIGHT_UP;
					}
					else {
						_nowz -= _spd;
						_direction = CHARA::STATE::LEFT_DOWN;
					}
				}
				else if (_nowx % BLOCKSIZE != 0) { 
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_z == 4) {
					_root = 13;
				}
				else if (_z < 4) {
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST1_2:   // ステージ1-2
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, _spd, 0, 2, 6, g); break;
			case 2:
				MoveRoot(0, 0, 0, -_spd, 3, 5, g); break;
			case 3:
				MoveRoot(0, 0, _spd, 0, 4, 3, g); break;
			case 4:
				MoveRoot(0, -1, 0, -_spd, 5, 0, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, 0, _spd, 7, 10, g); break;
			case 7:
				MoveRoot(1, 0, _spd, 0, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, 0, -_spd, 9, 7, g); break;
			case 9:
				MoveRoot(0, 0, -_spd, 0, 10, 9, g); break;
			case 10:
				MoveRoot(0, 0, 0, _spd, 1, 10, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 11:            
				MoveRoot(0, 0, 0, _spd, 12, 10, g); break;
			case 12:
				MoveRoot(0, 0, 0, _spd, 13, 11, g); break;
			case 13:
				MoveRoot(0, 0, 0, -_spd, 14, 10, g); break;
			case 14:
				MoveRoot(1, 0, _spd, 0, 15, 0, g); break;
			case 15:
				MoveRoot(0, -1, 0, -_spd, 16, 0, g); break;
			case 16:
				MoveRoot(-1, 0, -_spd, 0, 17, 0, g); break;
			case 17:
				MoveRoot(0, 0, 0, _spd, 11, 10, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {   
					if (_z < 4) {
						_nowz += _spd;
						_direction = CHARA::STATE::RIGHT_UP;
					}
					else {
						_nowz -= _spd;
						_direction = CHARA::STATE::LEFT_DOWN;
					}
				}
				else if (_nowx % BLOCKSIZE != 0) {  
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_x != 1) {
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_x == 1) {       
					_root = 11;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST1_3:   // ステージ1-3
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, _spd, 0, 2, 8, g); break;
			case 2:
				MoveRoot(0, 0, 0, _spd, 3, 12, g); break;
			case 3:
				MoveRoot(0, 0, -_spd, 0, 4, 13, g); break;
			case 4:
				MoveRoot(0, 0, 0, -_spd, 5, 11, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 1, 0, _spd, 7, 0, g); break;
			case 7:
				MoveRoot(0, 0, _spd, 0, 8, 14, g); break;
			case 8:
				MoveRoot(-1, 0, -_spd, 0, 9, 0, g); break;
			case 9:
				MoveRoot(0, -1, 0, -_spd, 10, 0, g); break;
			case 10:
				MoveRoot(0, 0, _spd, 0, 11, 11, g); break;
			case 11:
				MoveRoot(0, 0, 0, _spd, 12, 13, g); break;
			case 12:
				MoveRoot(0, 0, _spd, 0, 13, 12, g); break;
			case 13:
				MoveRoot(0, 0, 0, -_spd, 2, 8, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 14:        
				MoveRoot(0, 0, 0, -_spd, 15, 8, g); break;
			case 15:
				MoveRoot(0, 0, _spd, 0, 16, 7, g); break;
			case 16:
				MoveRoot(0, -1, 0, -_spd, 17, 0, g); break;
			case 17:
				MoveRoot(-1, 0, -_spd, 0, 18, 0, g); break;
			case 18:
				MoveRoot(0, 1, 0, _spd, 15, 0, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else if (_nowx % BLOCKSIZE != 0) {
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				else if (_x == 3) {                 
					_root = 14;
				}
				else {
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST2_1:   // ステージ2-1
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(1, 0, _spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, -1, 0, -_spd, 3, 0, g); break;
			case 3:
				MoveRoot(0, 0, -_spd, 0, 4, 7, g); break;
			case 4:
				MoveRoot(0, 0, 0, _spd, 5, 9, g); break;
			case 5:
				MoveRoot(0, 0, _spd, 0, 6, 5, g); break;
			case 6:
				MoveRoot(0, 1, 0, _spd, 7, 0, g); break;
			case 7:
				MoveRoot(0, 0, -_spd, 0, 8, 12, g); break;
			case 8:
				MoveRoot(0, -1, 0, -_spd, 9, 0, g); break;
			case 9:
				MoveRoot(0, -1, 0, -_spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 10:     
				MoveRoot(-1, 0, -_spd, 0, 11, 0, g); break;
			case 11:
				MoveRoot(0, 0, _spd, 0, 12, 8, g); break;
			case 12:
				MoveRoot(0, 0, 0, -_spd, 13, 6, g);  break;
			case 13:
				MoveRoot(-1, 0, -_spd, 0, 14, 0, g); break;
			case 14:
				MoveRoot(0, 0, 0, _spd, 11, 10, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) { 
					if (_z < 3) {
						_nowz += _spd;
						_direction = CHARA::STATE::RIGHT_UP;
					}
					else {
						_nowz -= _spd;
						_direction = CHARA::STATE::LEFT_DOWN;
					}
				}
				else if (_nowx % BLOCKSIZE != 0) { 
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_z == 3) {
					_root = 10;
				}
				else if (_z < 3) {
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST2_2:   // ステージ2-2
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, 0, _spd, 2, 7, g); break;
			case 2:
				MoveRoot(0, 0, _spd, 0, 3, 4, g); break;
			case 3:
				MoveRoot(0, -1, 0, -_spd, 4, 0, g); break;
			case 4:
				MoveRoot(0, 0, -_spd, 0, 5, 6, g); break;
			case 5:
				MoveRoot(0, 0, 0, _spd, 6, 9, g); break;
			case 6:
				MoveRoot(1, 0, _spd, 0, 7, 0, g); break;
			case 7:
				MoveRoot(0, -1, 0, -_spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, -_spd, 0, 1, 5, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 9:              
				MoveRoot(0, 0, 0, -_spd, 10, 8, g); break;
			case 10:
				MoveRoot(0, 0, 0, _spd, 11, 9, g); break;
			case 11:
				MoveRoot(0, 0, _spd, 0, 12, 0, g);  break;
			case 12:
				MoveRoot(0, -1, 0, -_spd, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, -_spd, 0, 14, 8, g); break;
			case 14:
				MoveRoot(0, 0, _spd, 0, 15, 6, g); break;
			case 15:
				MoveRoot(0, 0, 0, _spd, 16, 0, g); break;
			case 16:
				MoveRoot(0, 0, -_spd, 0, 17, 9, g); break;
			case 17:
				MoveRoot(0, -1, 0, -_spd, 10, 0, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {  
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_x == 1) {
					_root = 9;
				}
				else {
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST2_3:   // ステージ2-3
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, _spd, 0, 2, 4, g);  break;
			case 2:
				MoveRoot(0, 1, 0, _spd, 3, 0, g); break;
			case 3:
				MoveRoot(0, 0, -_spd, 0, 4, 9, g); break;
			case 4:
				MoveRoot(0, 0, 0, _spd, 5, 10, g); break;
			case 5:
				MoveRoot(0, 0, 0, -_spd, 6, 9, g); break;
			case 6:
				MoveRoot(-1, 0, -_spd, 0, 7, 0, g); break;
			case 7:
				MoveRoot(0, -1, 0, -_spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, _spd, 0, 9, 7, g); break;
			case 9:
				MoveRoot(0, 1, 0, _spd, 10, 0, g); break;
			case 10:
				MoveRoot(0, 0, -_spd, 0, 11, 12, g); break;
			case 11:
				MoveRoot(0, 0, 0, _spd, 12, 13, g); break;
			case 12:
				MoveRoot(0, -1, 0, -_spd, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, _spd, 0, 14, 11, g); break;
			case 14:
				MoveRoot(0, -1, 0, -_spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 15:     
				MoveRoot(0, 0, 0, -_spd, 16, 7, g); break;
			case 16:
				MoveRoot(0, 0, 0, _spd, 17, 13, g); break;
			case 17:
				MoveRoot(0, 0, 0, -_spd, 18, 7, g);  break;
			case 18:
				MoveRoot(0, 0, 0, _spd, 19, 9, g); break;
			case 19:
				MoveRoot(-1, 0, -_spd, 0, 20, 0, g); break;
			case 20:
				MoveRoot(0, 0, _spd, 0, 21, 9, g); break;
			case 21:
				MoveRoot(0, -1, 0, -_spd, 16, 0, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {  
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) { 
					if (_x < 4) {
						_nowx += _spd;
						_direction = CHARA::STATE::RIGHT_DOWN;
					}
					else {
						_nowx -= _spd;
						_direction = CHARA::STATE::LEFT_UP;
					}
				}
				else if (_x == 4) {
					_root = 15;
				}
				else if (_x < 4) {
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
	}
	_enemyAPosX = GetX();
	_enemyAPosZ = GetZ();

	_playTime += 0.7f;

	if (_playTime >= _totalTime){
		_playTime = 0.0f;
	}
}