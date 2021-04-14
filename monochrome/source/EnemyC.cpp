
/**
 * @file EnemyC.cpp
 * @brief �GC(�t���C�p��)�̈ړ�����
 *
 * @date 2020-09-24
 * @author �������F
 */

#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"

EnemyC::EnemyC(Game& g)
{
	_mh = MV1LoadModel("res/model/flypan.mv1");

	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);         
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex); 
	Init(g);
}

EnemyC::~EnemyC()
{
}

void EnemyC::Init(Game& g)
{
    // �����ʒu&����
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:
		_x = 100; _z = 100; break;
	case GAME::STAGENO::ST1_1:
		_x = 5; _z = 1; _spd = 2; break;
	case GAME::STAGENO::ST1_2:
		_x = 5; _z = 1; _spd = 3; break;
	case GAME::STAGENO::ST1_3:
		_x = 4; _z = 7; _spd = 1; break;
	case GAME::STAGENO::ST2_1:
		_x = 1; _z = 6; _spd = 3; break;
	case GAME::STAGENO::ST2_2:
		_x = 1; _z = 4; _spd = 2; break;
	case GAME::STAGENO::ST2_3:
		_x = 1; _z = 7; _spd = 2; break;
	}
	_r = 40;
	_movx = 0;
	_movz = 0;
	_nowx = _x * BLOCKSIZE;   //�h�b�g�ړ��ɂ���
	_nowz = _z * BLOCKSIZE;   //�h�b�g�ړ��ɂ���
	_nowy = 90;
	_root = 1;
	_direction = 2;

	_playTime = 0.0f;
}

void EnemyC::Process(Game& g)
{
	EnemyBase::Process(g);

	// �ʒu�Ǘ�(�u���b�N�ԍ�)
	if (_nowx % BLOCKSIZE == 0 && _nowz % BLOCKSIZE == 0) {
		_x = _nowx / BLOCKSIZE;
		_z = _nowz / BLOCKSIZE;
	}

	switch (g._gStageNo) {
	case GAME::STAGENO::ST1_1:    // �X�e�[�W1-1
        // �L���E���N��߂܂���O�̈ړ����[�g
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(1, 0, _spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, 0, 0, _spd, 3, 5, g); break;
			case 3:
				MoveRoot(-1, 0, -_spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, -1, 0, -_spd, 5, 0, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, 0, _spd, 7, 13, g); break;
			case 7:
				MoveRoot(1, 0, _spd, 0, 8, 0, g); break;
			case 8:
				MoveRoot(0, -1, 0, -_spd, 1, 0, g); break;
			}
		}
		//�L���E���N��߂܂�����̈ړ����[�g
		if (g._gHasKyuri == true) {
			switch (_root) {
			case 9:                        //�����ʒu�ֈړ�
				MoveRoot(0, 0, 0, -_spd, 10, 7, g); break;
			case 10:
				MoveRoot(0, 1, 0, _spd, 11, 0, g); break;
			case 11:
				MoveRoot(0, 0, _spd, 0, 12, 11, g); break;
			case 12:
				MoveRoot(0, -1, 0, -_spd, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, -_spd, 0, 10, 7, g); break;
			default:
				//���[�g�ؑ֎��A���r���[�ȍ��W�ɂ����ꍇ�͈ʒu����������Ď��̃��[�g�Ɉڂ�悤�ɂ���(�듮��h�~)
				if (_nowz % BLOCKSIZE != 0) {       // ���݈ʒu���W�������iZ���W�j
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {  // ���݈ʒu���W�������iX���W�j
					if (_x > 4) {
						_nowx -= _spd;
						_direction = CHARA::STATE::LEFT_UP;
					}
					else {
						_nowx += _spd;
						_direction = CHARA::STATE::RIGHT_DOWN;
					}
				}
				else if (_x == 4) {                 
					_root = 9;
				}
				else if (_x > 4) {
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else {
					_nowx += _spd;
					_direction = CHARA::STATE::RIGHT_DOWN;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST1_2:   // �X�e�[�W1-2
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(1, 0, _spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, 1, 0, _spd, 3, 0, g); break;
			case 3:
				MoveRoot(0, 0, -_spd, 0, 4, 10, g); break;
			case 4:
				MoveRoot(0, -1, 0, -_spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 5:                
				MoveRoot(0, 0, 0, -_spd, 6, 4, g); break;
			case 6:
				MoveRoot(0, 1, 0, _spd, 7, 0, g); break;
			case 7:
				MoveRoot(-1, 0, -_spd, 0, 8, 0, g); break;
			case 8:
				MoveRoot(0, -1, 0, -_spd, 9, 0, g); break;
			case 9:
				MoveRoot(0, 0, _spd, 0, 6, 4, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) { 
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;

				}
				else if (_x == 5) {                
					_root = 5;
				}
				else {
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST1_3:   // �X�e�[�W1-3
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, -1, 0, -_spd, 2, 0, g); break;
			case 2:
				MoveRoot(0, 1, 0, _spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 3:          
				MoveRoot(0, 0, 0, _spd, 4, 11, g); break;
			case 4:
				MoveRoot(0, 0, 0, -_spd, 5, 9, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 6, 0, g); break;
			case 6:
				MoveRoot(0, 0, 0, _spd, 7, 14, g); break;
			case 7:
				MoveRoot(0, 0, _spd, 0, 8, 11, g); break;
			case 8:
				MoveRoot(0, 0, 0, -_spd, 9, 9, g); break;
			case 9:
				MoveRoot(1, 0, _spd, 0, 10, 0, g); break;
			case 10:
				MoveRoot(0, 0, 0, _spd, 11, 8, g); break;
			case 11:
				MoveRoot(0, 0, -_spd, 0, 4, 11, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {  
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else {                             
					_root = 3;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST2_1:   // �X�e�[�W2-1
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(0, 1, 0, _spd, 2, 0, g); break;
			case 2:
				MoveRoot(0, 0, _spd, 0, 3, 14, g); break;
			case 3:
				MoveRoot(0, 0, 0, -_spd, 4, 10, g); break;
			case 4:
				MoveRoot(0, 1, 0, _spd, 5, 0, g); break;
			case 5:
				MoveRoot(-1, 0, -_spd, 0, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 6:                 
				MoveRoot(0, 0, -_spd, 0, 7, 13, g); break;
			case 7:
				MoveRoot(0, 0, 0, -_spd, 8, 0, g); break;
			case 8:
				MoveRoot(0, 1, _spd, 0, 9, 11, g); break;
			case 9:
				MoveRoot(0, -1, 0, -_spd, 10, 8, g); break;
			case 10:
				MoveRoot(0, 0, -_spd, 0, 11, 10, g); break;
			case 11:
				MoveRoot(0, 0, 0, _spd, 12, 12, g); break;
			case 12:
				MoveRoot(-1, 0, -_spd, 0, 13, 0, g); break;
			case 13:
				MoveRoot(0, 0, _spd, 0, 14, 11, g); break;
			case 14:
				MoveRoot(0, 0, 0, -_spd, 15, 0, g); break;
			case 15:
				MoveRoot(1, 0, -_spd, 0, 16, 11, g); break;
			case 16:
				MoveRoot(0, 0, 0, _spd, 7, 13, g); break;
			case 17:
				MoveRoot(0, 0, 0, _spd, 18, 7, g); break;
			case 18:
				MoveRoot(0, 0, _spd, 0, 19, 6, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {  
					if (_z > 6) {
						_nowz -= _spd;
						_direction = CHARA::STATE::LEFT_DOWN;
					}
					else {
						_nowz += _spd;
						_direction = CHARA::STATE::RIGHT_UP;
					}
				}
				else if (_nowx % BLOCKSIZE != 0) { 
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;

				}
				else if (_z == 6) {               
					_root = 6;
				}
				else if (_z > 6) {
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else {
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				break;
			}
		}
		break;

	case GAME::STAGENO::ST2_2:   // �X�e�[�W2-2
			if (g._gHasKyuri == false && g._gHasLanding == true) {
				switch (_root) {
				case 1:
					MoveRoot(0, 0, 0, _spd, 2, 13, g); break;
				case 2:
					MoveRoot(1, 0, _spd, 0, 3, 7, g); break;
				case 3:
					MoveRoot(0, -1, 0, -_spd, 4, 3, g); break;
				case 4:
					MoveRoot(0, 0, -_spd, 0, 5, 9, g); break;
				case 5:
					MoveRoot(0, 0, 0, _spd, 6, 12, g); break;
				case 6:
					MoveRoot(0, 0, _spd, 0, 7, 0, g); break;
				case 7:
					MoveRoot(0, -2, 0, -_spd, 8, 7, g); break;
				case 8:
					MoveRoot(0, 0, -_spd, 0, 9, 10, g); break;
				case 9:
					MoveRoot(0, 0, 0, _spd, 1, 11, g); break;
				}
			}

			if (g._gHasKyuri == true) {
				switch (_root) {
				case 10:              
					MoveRoot(0, 0, -_spd, 0, 11, 11, g); break;
				case 11:
					MoveRoot(0, 0, 0, -_spd, 12, 9, g); break;
				case 12:
					MoveRoot(0, 0, 0, _spd, 13, 12, g); break;
				case 13:
					MoveRoot(0, 0, 0, -_spd, 14, 9, g); break;
				case 14:
					MoveRoot(0, 0, 0, _spd, 15, 11, g); break;
				case 15:
					MoveRoot(0, 0, _spd, 0, 16, 10, g); break;
				case 16:
					MoveRoot(-1, 0, -_spd, 0, 11, 0, g); break;
				default:
					if (_nowz % BLOCKSIZE != 0) { 
						if (_z > 4) {
							_nowz -= _spd;
							_direction = CHARA::STATE::LEFT_DOWN;
						}
						else {
							_nowz += _spd;
							_direction = CHARA::STATE::RIGHT_UP;
						}
					}
					else if (_nowx % BLOCKSIZE != 0) {
						_nowx -= _spd;
						_direction = CHARA::STATE::LEFT_UP;

					}
					else if (_z == 4) {                
						_root = 10;
					}
					else if (_z > 4) {
						_nowz -= _spd;
						_direction = CHARA::STATE::LEFT_DOWN;
					}
					else {
						_nowz += _spd;
						_direction = CHARA::STATE::RIGHT_UP;
					}
					break;
				}
			}
			break;
	case GAME::STAGENO::ST2_3:   // �X�e�[�W2-3
		if (g._gHasKyuri == false && g._gHasLanding == true) {
			switch (_root) {
			case 1:
				MoveRoot(1, 0, _spd, 0, 2, 0, g); break;
			case 2:
				MoveRoot(0, -1, 0, -_spd, 3, 0, g); break;
			case 3:
				MoveRoot(-1, 0, -_spd, 0, 4, 0, g); break;
			case 4:
				MoveRoot(0, 1, 0, _spd, 1, 0, g); break;
			}
		}

		if (g._gHasKyuri == true) {
			switch (_root) {
			case 5:            
				MoveRoot(0, 0, 0, _spd, 6, 16, g); break;
			case 6:
				MoveRoot(0, 0, _spd, 0, 7, 14, g); break;
			case 7:
				MoveRoot(0, -1, 0, -_spd, 8, 0, g); break;
			case 8:
				MoveRoot(-1, 0, -_spd, 0, 9, 0, g); break;
			case 9:
				MoveRoot(0, 0, 0, _spd, 6, 16, g); break;
			default:
				if (_nowz % BLOCKSIZE != 0) {    
					_nowz += _spd;
					_direction = CHARA::STATE::RIGHT_UP;
				}
				else if (_nowx % BLOCKSIZE != 0) { 
					_nowx -= _spd;
					_direction = CHARA::STATE::LEFT_UP;
				}
				else if (_x == 1) {                 
					_root = 5;
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