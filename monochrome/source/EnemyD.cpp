
/**
 * @file EnemyD.cpp
 * @brief �GD(�t���C�p��)�̈ړ�����
 *
 * @date 2020-09-24
 * @author �������F
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
	// �����ʒu&����
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
	_nowx = _x * BLOCKSIZE;   //�h�b�g�ړ��ɂ���
	_nowz = _z * BLOCKSIZE;   //�h�b�g�ړ��ɂ���
	_nowy = 90;
	_root = 1;
	_direction = 2;
	// �Đ����Ԃ̏�����
	_playTime = 0.0f;
}

void EnemyD::Process(Game& g)
{
	EnemyBase::Process(g);

	// �ʒu�Ǘ�(�u���b�N�ԍ�)
	if (_nowx % BLOCKSIZE == 0 && _nowz % BLOCKSIZE == 0) {
		_x = _nowx / BLOCKSIZE;
		_z = _nowz / BLOCKSIZE;
	}

	switch (g._gStageNo) {
	case GAME::STAGENO::ST2_1:   // �X�e�[�W2-1
		//�L���E���N��߂܂���O�̈ړ����[�g
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
		//�L���E���N��߂܂�����̈ړ����[�g
		if (g._gHasKyuri == true) {
			switch (_root) {
			case 9:                        //�����ʒu�ֈړ�
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
				//���[�g�ؑ֎��A���r���[�ȍ��W�ɂ����ꍇ�͈ʒu����������Ď��̃��[�g�Ɉڂ�悤�ɂ���(�듮��h�~)
				if (_nowz % BLOCKSIZE != 0) {       // ���݈ʒu���W�������iZ���W�j
					_nowz -= _spd;
					_direction = CHARA::STATE::LEFT_DOWN;
				}
				else if (_nowx % BLOCKSIZE != 0) {  // ���݈ʒu���W�������iX���W�j
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

	case GAME::STAGENO::ST2_2:   // �X�e�[�W2-2
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
	case GAME::STAGENO::ST2_3:  // �X�e�[�W2-3
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