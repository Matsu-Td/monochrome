/** 
 * @file   Enemy.cpp
 * @brief  �G�l�~�[(�L���E���N)�N���X
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "Enemy.h"
#include "game.h"
#include "ResourceServer.h"

Enemy::Enemy(Game& g)
{
	_cg = ResourceServer::LoadGraph("res/kyuritatie.png");         

	Init(g);
}

Enemy::~Enemy()
{
}

void Enemy::Init(Game& g)
{
	//�����ʒu
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:     
		_x = 7; _z = 7; break;
	case GAME::STAGENO::ST1_1:
		_x = 4; _z = 4; break;
	case GAME::STAGENO::ST1_2:
		_x = 5; _z = 2; break;
	case GAME::STAGENO::ST1_3:
		_x = 2; _z = 7; break;
	case GAME::STAGENO::ST2_1:
		_x = 6; _z = 5; break;
	case GAME::STAGENO::ST2_2:
		_x = 3; _z = 4; break;
	case GAME::STAGENO::ST2_3:
		_x = 9; _z = 1; break;
	}

	_y = 0;
	_w = 220.0f;
	_r = 40;
	_alpha = 0;
	_movx = 1;
	_movz = 1;
	_lateCnt = MOVE_FLAME;

	Player* player = new Player(g);
	_plX = player->GetX(); _plZ = player->GetZ();  //�v���C���[�̏����ʒu
}

void Enemy::Process(Game& g)
{
	ObjectBase::Process(g);
	
	//�����蔻��p
	_nowx = _x * BLOCKSIZE;
	_nowz = _z * BLOCKSIZE;

	//�GA�Ƃ̋������v�Z
	_disX = EnemyA::_enemyAPosX - GetX();
	_disZ = EnemyA::_enemyAPosZ - GetZ();

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			// �i�X�N��1�O�̃u���b�N�̈ʒu����
			_oldPlX = (*ite)->GetX();
			_oldPlZ = (*ite)->GetZ();
		}
	}

	if (_plX != _oldPlX || _plZ != _oldPlZ) {
		--_lateCnt;
		if (_lateCnt == 0) {
			//�ړ���̃u���b�N������������ړ�����A�GA�̈ʒu�ɂ���ĕ���		
			if (_disX > 0) {
				if (g._gCharaMap[_z][_x + _movx] != 0) {
					++_x;
				}
				else if (_disZ > 0) {
					if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else {
						--_x;
					}
				}
				else if (_disZ < 0) {
					if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else {
						--_x;
					}
				}
				else if (_disZ == 0) {
					if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else {
						--_x;
					}
				}
				_lateCnt = MOVE_FLAME;
			}
			if (_disX < 0) {
				if (g._gCharaMap[_z][_x - _movx] != 0) {
					--_x;
				}
				else if (_disZ > 0) {
					if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else {
						++_x;
					}
				}
				else if (_disZ < 0) {
					if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else if (g._gCharaMap[_z - _movz][_x] != 0) {
						++_z;
					}
					else {
						++_x;
					}
				}
				else if (_disZ == 0) {
					if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else {
						++_x;
					}
				}
				_lateCnt = MOVE_FLAME;
			}
			if (_disX == 0) {
				if (_disZ > 0) {
					if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else if (g._gCharaMap[_z][_x + _movx] != 0) {
						++_x;
					}
					else {
						--_x;
					}
				}
				else if (_disZ < 0) {
					if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else if (g._gCharaMap[_z][_x + _movx] != 0) {
						++_x;
					}
					else {
						--_x;
					}
				}
				else if (_disZ == 0) {
					if (g._gCharaMap[_z - _movz][_x] != 0) {
						--_z;
					}
					else if (g._gCharaMap[_z + _movz][_x] != 0) {
						++_z;
					}
					else if (g._gCharaMap[_z][_x + _movx] != 0) {
						++_x;
					}
					else if (g._gCharaMap[_z][_x - _movx] != 0) {
						--_x;
					}
				}
				_lateCnt = MOVE_FLAME;
			}

			for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
				if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
					// �i�X�N�̌��݂̃u���b�N�ʒu����
					_plX = (*ite)->GetX();
					_plZ = (*ite)->GetZ();
				}
			}
		}
	}

	//���K�̉��ʐݒ�
	PianoSound _pianoSound;
	_pianoSound.VolumeCheck(g, GetX(), GetZ(), _oldPlX, _oldPlZ);

	//���K�o�͏���
	_pianoSound.SoundOutput(g, _oldEnPos, g._gCharaMap[_z][_x]);

	_oldEnPos = g._gCharaMap[_z][_x];         // �����Ō��݂̈ʒu�ƈ���O�̈ʒu�𓯂��ɂ���

	// �L���E���N�ƃi�X�N�̓����蔻��
	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			if (IsHit(*(*ite)) == true) {
				//�����𐶐��ˉ����l�����o
				Note* note = new Note(g);
				note->SetPosition(_x* BLOCKSIZE, _y, _z* BLOCKSIZE);
				g._objServer.Add(note);
				Damage(g);	
			}
		}
	}
}
void Enemy::Draw(Game& g)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	DrawBillboard3D(VGet(static_cast<float>(_x) * BLOCKSIZE, static_cast<float>(_y), static_cast<float>(_z) * BLOCKSIZE), 0.5f, 0.2f, _w, 0.0f, _cg, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Enemy::Damage(Game& g)
{
	g._gHasKyuri = true;   //�L���E���N�߂܂�A�S�[���o���t���O
	StopMusic();
	PlaySoundMem(g._se["bgm08"], DX_PLAYTYPE_LOOP);
	PlaySoundMem(g._se["nyuusyu"], DX_PLAYTYPE_BACK);
	g._objServer.Del(this);
}