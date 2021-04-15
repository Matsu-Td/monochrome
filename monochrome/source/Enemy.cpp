/** 
 * @file   Enemy.cpp
 * @brief  エネミー(キュウリ君)クラス
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
	//初期位置
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
	_plX = player->GetX(); _plZ = player->GetZ();  //プレイヤーの初期位置
}

void Enemy::Process(Game& g)
{
	ObjectBase::Process(g);
	
	//当たり判定用
	_nowx = _x * BLOCKSIZE;
	_nowz = _z * BLOCKSIZE;

	//敵Aとの距離を計算
	_disX = EnemyA::_enemyAPosX - GetX();
	_disZ = EnemyA::_enemyAPosZ - GetZ();

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			// ナス君の1つ前のブロックの位置を代入
			_oldPlX = (*ite)->GetX();
			_oldPlZ = (*ite)->GetZ();
		}
	}

	if (_plX != _oldPlX || _plZ != _oldPlZ) {
		--_lateCnt;
		if (_lateCnt == 0) {
			//移動先のブロックが道だったら移動する、敵Aの位置によって分岐		
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
					// ナス君の現在のブロック位置を代入
					_plX = (*ite)->GetX();
					_plZ = (*ite)->GetZ();
				}
			}
		}
	}

	//音階の音量設定
	PianoSound _pianoSound;
	_pianoSound.VolumeCheck(g, GetX(), GetZ(), _oldPlX, _oldPlZ);

	//音階出力処理
	_pianoSound.SoundOutput(g, _oldEnPos, g._gCharaMap[_z][_x]);

	_oldEnPos = g._gCharaMap[_z][_x];         // ここで現在の位置と一歩前の位置を同じにする

	// キュウリ君とナス君の当たり判定
	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			if (IsHit(*(*ite)) == true) {
				//音符を生成⇒音符獲得演出
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
	g._gHasKyuri = true;   //キュウリ君捕まる、ゴール出現フラグ
	StopMusic();
	PlaySoundMem(g._se["bgm08"], DX_PLAYTYPE_LOOP);
	PlaySoundMem(g._se["nyuusyu"], DX_PLAYTYPE_BACK);
	g._objServer.Del(this);
}