/** 
 * @file   EnemyB.cpp
 * @brief  エネミー(フライパンB)クラス
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"

EnemyB::EnemyB(Game& g)
{
	_mh = MV1LoadModel("res/model/flypan.mv1");

	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);      
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex); 
	Init(g);
}

EnemyB::~EnemyB()
{
}

void EnemyB::Init(Game& g)
{
 // 初期位置&速さ
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:
		_x = 7; _z = 1; _spd = 1; break;
	case GAME::STAGENO::ST1_1:
		_x = 6; _z = 7; _spd = 1; break;
	case GAME::STAGENO::ST1_2:
		_x = 1; _z = 6; _spd = 2; break;
	case GAME::STAGENO::ST1_3:
		_x = 7; _z = 3; _spd = 3; break;
	case GAME::STAGENO::ST2_1:
		_x = 5; _z = 10; _spd = 1; break;
	case GAME::STAGENO::ST2_2:
		_x = 4; _z = 7; _spd = 1; break;
	case GAME::STAGENO::ST2_3:
		_x = 9; _z = 3; _spd = 1; break;
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

void EnemyB::Process(Game& g)
{
	EnemyBase::Process(g);

	// 位置管理(ブロック番号)
	if (_nowx % BLOCKSIZE == 0 && _nowz % BLOCKSIZE == 0) {
		_x = _nowx / BLOCKSIZE;
		_z = _nowz / BLOCKSIZE;
	}
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:   // チュートリアル
	// キュウリ君を捕まえる前の移動ルート
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 1, 0, _spd, 2, 0, g); break;
			case 2:
				MoveRoot(0, 0, -_spd, 0, 3, 11, g); break;
			case 3:
				MoveRoot(0, 0, 0, -_spd, 4, 8, g); break;
			case 4:
				MoveRoot(0, 0, _spd, -0, 5, 7, g); break;
			case 5:
				MoveRoot(0, 0, 0, -_spd, 6, 4, g); break;
			case 6:
				MoveRoot(1, 0, _spd, 0, 7, 0, g); break;
			case 7:
				MoveRoot(0, 1, 0, _spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, -_spd, 0, 9, 11, g); break;
			case 9:
				MoveRoot(0, -1, 0, -_spd, 10, 0, g); break;
			case 10:
				MoveRoot(1, 0, _spd, 0, 1, 0, g); break;
			}
		}

		// キュウリ君を捕まえた後の移動ルート
		if (g._gHasKyuri == true) {
			switch (_root) {
			case 11:              // 初期位置へ移動
				MoveRoot(0, 0, _spd, 0, 12, 2, g); break;
			case 12:
				MoveRoot(0, 1, 0, _spd, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, -_spd, 0, 14, 11, g); break;
			case 14:
				MoveRoot(0, 0, 0, -_spd, 15, 8, g); break;
			case 15:
				MoveRoot(1, 0, _spd, 0, 16, 0, g); break;
			case 16:
				MoveRoot(0, -1, 0, -_spd, 12, 0, g); break;
			default:
				// ルート切替時、中途半端な座標にいた場合は位置を微調整して次のルートに移るようにする(誤動作防止)
				if (_nowz % BLOCKSIZE != 0) {       // 現在位置座標微調整（Z座標）
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {  // 現在位置座標微調整（X座標）
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				else if (_z == 1) {
					_root = 11;
				}
				else {                
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST1_1:   // ステージ1-1
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, -_spd, 0, 2, 12, g); break;
			case 2:
				MoveRoot(0, 0, 0, -_spd, 3, 0, g); break;
			case 3:
				MoveRoot(0, 0, _spd, 0, 4, 10, g); break;
			case 4:
				MoveRoot(0, 0, 0, -_spd, 5, 5, g); break;
			case 5:
				MoveRoot(0, 0, _spd, 0, 6, 3, g); break;
			case 6:
				MoveRoot(0, 0, 0, _spd, 7, 6, g); break;
			case 7:
				MoveRoot(0, 0, -_spd, 0, 8, 7, g); break;
			case 8:
				MoveRoot(0, 0, 0, _spd, 9, 10, g); break;
			case 9:
				MoveRoot(0, 0, -_spd, 0, 10, 11, g); break;
			case 10:
				MoveRoot(0, 0, _spd, 0, 11, 8, g); break;
			case 11:
				MoveRoot(0, 0, 0, -_spd, 12, 5, g); break;
			case 12:
				MoveRoot(0, 0, -_spd, 0, 13, 8, g); break;
			case 13:
				MoveRoot(0, 0, 0, _spd, 1, 11, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 14:    
				MoveRoot(0, 0, -_spd, 0, 15, 16, g); break;
			case 15:
				MoveRoot(0, 0, 0, -_spd, 16, 14, g); break;
			case 16:
				MoveRoot(1, 0, _spd, 0, 17, 11, g); break;
			case 17:
				MoveRoot(0, -2, 0, -_spd, 18, 8, g); break;
			case 18:
				MoveRoot(0, 0, _spd, 0, 19, 9, g); break;
			case 19:
				MoveRoot(0, 0, 0, _spd, 20, 13, g); break;
			case 20:
				MoveRoot(0, 0, 0, -_spd, 21, 9, g); break;
			case 21:
				MoveRoot(0, 0, -_spd, 0, 22, 0, g); break;
			case 22:
				MoveRoot(0, 2, 0, _spd, 23, 14, g); break;
			case 23:
				MoveRoot(0, 0, -_spd, 0, 24, 14, g); break;
			case 24:
				MoveRoot(0, 0, 0, _spd, 25, 16, g); break;
			case 25:
				MoveRoot(0, 0, _spd, 0, 14, 13, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {  
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else if (_nowx % BLOCKSIZE != 0) {  
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_z == 7) {
					_root = 14;		
				}
				else{                
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST1_2:   // ステージ1-2
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 1, 0, _spd, 2, 0, g); break;
			case 2:
				MoveRoot(0, 0, _spd, 0, 3, 10, g); break;
			case 3:
				MoveRoot(0, 0, 0, -_spd, 4, 7, g); break;
			case 4:
				MoveRoot(0, 0, 0, _spd, 5, 8, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, 0, _spd, 7, 13, g); break;
			case 7:
				MoveRoot(2, 0, _spd, 0, 8, 9, g); break;
			case 8:
				MoveRoot(0, 0, 0, -_spd, 9, 10, g); break;
			case 9:
				MoveRoot(1, 0, _spd, 0, 10, 0, g); break;
			case 10:
				MoveRoot(0, 0, 0, -_spd, 11, 6, g); break;
			case 11:
				MoveRoot(0, 0, 0, _spd, 12, 8, g); break;
			case 12:
				MoveRoot(-1, 0, -_spd, 0, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, 0, _spd, 1, 13, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 14:         
				MoveRoot(0, 0, -_spd, 0, 15, 13, g); break;
			case 15:                        
				MoveRoot(0, 0, 0, -_spd, 16, 11, g); break;
			case 16:
				MoveRoot(0, 0, 0, _spd, 17, 12, g); break;
			case 17:
				MoveRoot(0, 0, _spd, 0, 18, 11, g); break;
			case 18:
				MoveRoot(0, 0, 0, _spd, 19, 13, g); break;
			case 19:
				MoveRoot(-1, 0, -_spd, 0, 20, 0, g); break;
			case 20:
				MoveRoot(0, 0, 0, -_spd, 21, 12, g); break;
			case 21:
				MoveRoot(0, 0, _spd, 0, 22, 9, g); break;
			case 22:
				MoveRoot(-1, 0, -_spd, 0, 23, 0, g); break;
			case 23:
				MoveRoot(0, 0, 0, _spd, 15, 13, g); break;
			default:
                if (_nowz % BLOCKSIZE != 0) {    
					if (_z < 6) {
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
				else if (_z == 6) {
					_root = 14;
				}
				else if (_z < 6) {               
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

	case GAME::STAGENO::ST1_3:   // ステージ1-3
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 0, 0, _spd, 2, 6, g); break;
			case 2:
				MoveRoot(0, 0, -_spd, 0, 3, 9, g); break;
			case 3:
				MoveRoot(0, 1, 0, _spd, 4, 0, g); break;
			case 4:
				MoveRoot(1, 0, _spd, 0, 5, 0, g); break;
			case 5:
				MoveRoot(0, 1, 0, _spd, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, -_spd, 0, 7, 13, g); break;
			case 7:
				MoveRoot(1, 0, _spd, 0, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, 0, -_spd, 9, 8, g); break;
			case 9:
				MoveRoot(0, 0, -_spd, 0, 10, 11, g); break;
			case 10:
				MoveRoot(0, 0, 0, -_spd, 11, 9, g); break;
			case 11:
				MoveRoot(1, 0, _spd, 0, 2, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 12:              
				MoveRoot(0, 0, 0, -_spd, 13, 6, g); break;
			case 13:
				MoveRoot(0, 0, -_spd, 0, 14, 9, g); break;
			case 14:
				MoveRoot(0, 0, 0, -_spd, 15, 7, g); break;
			case 15:
				MoveRoot(1, 0, _spd, 0, 16, 0, g); break;
			case 16:
				MoveRoot(0, -1, 0, -_spd, 17, 0, g); break;
			case 17:
				MoveRoot(0, 0, -_spd, 0, 18, 4, g); break;
			case 18:
				MoveRoot(0, 0, 0, _spd, 19, 0, g); break;
			case 19:
				MoveRoot(0, 0, -_spd, 0, 20, 6, g); break;
			case 20:
				MoveRoot(0, 0, 0, _spd, 21, 8, g); break;
			case 21:
				MoveRoot(0, 0, 0, -_spd, 22, 6, g); break;
			case 22:
				MoveRoot(0, 0, _spd, 0, 23, 0, g); break;
			case 23:
				MoveRoot(0, 0, 0, _spd, 24, 6, g); break;
			case 24:
				MoveRoot(0, 0, _spd, 0, 25, 5, g); break;
			case 25:
				MoveRoot(0, 0, 0, _spd, 26, 0, g); break;
			case 26:
				MoveRoot(0, 0, -_spd, 0, 14, 8, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {  
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else if (_nowx % BLOCKSIZE != 0) {  
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				else if (_x == 7) {                 
					_root = 12;
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
				MoveRoot(-1, 0, -_spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, -1, 0, -_spd, 3, 0, g); break;
			case 3:
				MoveRoot(1, 0, _spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, 0, 0, _spd, 5, 9, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 1, 0, _spd, 7, 0, g); break;
			case 7:
				MoveRoot(0, -1, 0, -_spd, 8, 0, g); break;
			case 8:
				MoveRoot(1, 0, _spd, 0, 9, 0, g); break;
			case 9:
				MoveRoot(0, 0, 0, _spd, 10, 9, g); break;
			case 10:
				MoveRoot(-1, 0, -_spd, 0, 11, 0, g); break;
			case 11:
				MoveRoot(0, 1, 0, _spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 12: 
				MoveRoot(0, 0, 0, -_spd, 13, 6, g); break;
			case 13:
				MoveRoot(0, 0, 0, -_spd, 14, 4, g); break;
			case 14:
				MoveRoot(0, 0, -_spd, 0, 15, 5, g); break;
			case 15:
				MoveRoot(0, 0, 0, _spd, 16, 10, g); break;
			case 16:
				MoveRoot(0, 0, _spd, 0, 17, 9, g); break;
			case 17:
				MoveRoot(0, 0, 0, -_spd, 18, 6, g); break;
			case 18:
				MoveRoot(1, 0, _spd, 0, 19, 0, g); break;
			case 19:
				MoveRoot(0, 0, 0, -_spd, 20, 3, g); break;
			case 20:
				MoveRoot(0, 0, -_spd, 0, 21, 0, g); break;
			case 21:
				MoveRoot(0, -1, 0, -_spd, 22, 0, g); break;
			case 22:
				MoveRoot(0, 0, -_spd, 0, 23, 5, g); break;
			case 23:
				MoveRoot(0, 0, 0, _spd, 24, 7, g); break;
			case 24:
				MoveRoot(0, 0, _spd, 0, 13, 6, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {  
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) { 
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
					_root = 12;
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
				MoveRoot(1, 0, _spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, 0, 0, -_spd, 3, 5, g); break;
			case 3:
				MoveRoot(0, 0, -_spd, 0, 4, 8, g); break;
			case 4:
				MoveRoot(0, 1, 0, _spd, 5, 0, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, _spd, 0, 7, 13, g); break;
			case 7:
				MoveRoot(0, 0, 0, -_spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, _spd, 0, 9, 10, g); break;
			case 9:
				MoveRoot(0, 1, 0, _spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 12:           
				MoveRoot(0, 0, 0, -_spd, 13, 5, g); break;
			case 13:
				MoveRoot(0, 0, -_spd, 0, 14, 8, g); break;
			case 14:
				MoveRoot(0, -1, 0, -_spd, 15, 0, g); break;
			case 15:
				MoveRoot(0, 0, -_spd, 0, 16, 6, g); break;
			case 16:
				MoveRoot(0, 1, 0, _spd, 17, 9, g); break;
			case 17:
				MoveRoot(-1, 0, -_spd, 0, 18, 10, g); break;
			case 18:
				MoveRoot(0, 2, 0, _spd, 19, 13, g); break;
			case 19:
				MoveRoot(0, 0, _spd, 0, 20, 9, g); break;
			case 20:
				MoveRoot(0, 0, 0, _spd, 21, 10, g); break;
			case 21:
				MoveRoot(0, 0, -_spd, 0, 22, 13, g); break;
			case 22:
				MoveRoot(0, 0, 0, -_spd, 23, 12, g); break;
			case 23:
				MoveRoot(0, 0, _spd, 0, 14, 9, g); break;
			case 24:
				MoveRoot(0, 0, _spd, 0, 13, 6, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {  
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				else if (_x == 7) {                
					_root = 12;
				}
				else {
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST2_3:   // ステージ2-3
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 1, 0, _spd, 2, 0, g); break;
			case 2:
				MoveRoot(0, 0, -_spd, 0, 3, 10, g); break;
			case 3:
				MoveRoot(0, 0, 0, -_spd, 4, 5, g); break;
			case 4:
				MoveRoot(1, 0, _spd, 0, 5, 0, g); break;
			case 5:
				MoveRoot(0, 0, 0, _spd, 6, 7, g); break;
			case 6:
				MoveRoot(-1, 0, -_spd, 0, 7, 0, g); break;
			case 7:
				MoveRoot(0, -1, 0, -_spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 0, -_spd, 0, 9, 11, g); break;
			case 9:
				MoveRoot(0, 0, 0, -_spd, 10, 9, g); break;
			case 10:
				MoveRoot(1, 0, _spd, 0, 11, 0, g); break;
			case 11:
				MoveRoot(0, -1, 0, -_spd, 12, 0, g); break;
			case 12:
				MoveRoot(1, 0, _spd, 0, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, 0, _spd, 1, 4, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 14:          
				MoveRoot(0, 0, 0, _spd, 15, 9, g); break;
			case 15:
				MoveRoot(0, 0, -_spd, 0, 16, 13, g); break;
			case 16:
				MoveRoot(0, 0, 0, _spd, 17, 14, g); break;
			case 17:
				MoveRoot(0, 0, _spd, 0, 18, 10, g); break;
			case 18:
				MoveRoot(0, -1, 0, -_spd, 19, 0, g); break;
			case 19:
				MoveRoot(0, 0, -_spd, 0, 20, 10, g); break;
			case 20:
				MoveRoot(0, 1, 0, _spd, 21, 0, g); break;
			case 21:
				MoveRoot(0, 0, _spd, 0, 22, 10, g); break;
			case 22:
				MoveRoot(0, 0, 0, -_spd, 15, 9, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {   
					_nowz -= _spd;
				}
				else if (_nowx % BLOCKSIZE != 0) {
					if (_x < 7) {
						_nowx += _spd;
						_direction = CHARA::STATE::RIGHT_DOWN;
					}
					else {
						_nowx -= _spd;
						_direction = CHARA::STATE::LEFT_UP;
					}
				}
				else if (_z > 6) {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_x == 7) {               
					_root = 14;
				}
				else if (_x < 7) {
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

	_playTime += 0.7f;

	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}
}