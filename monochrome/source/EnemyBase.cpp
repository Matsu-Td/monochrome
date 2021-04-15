/** 
 * @file   EnemyBase.cpp
 * @brief  �G�l�~�[(�t���C�p��)���N���X
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "EnemyBase.h"
#include "game.h"
#include "ResourceServer.h"

EnemyBase::EnemyBase()
{
	Init();
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{

}

/**
 * �ړ����[�g����
 */
void EnemyBase::MoveRoot(int movx, int movz, int nowx, int nowz, int root, int id, Game& g)
{
	// �ړ���������
	if (g._gCharaMap[_z + movz][_x + movx] != id) { _nowx += nowx; _nowz += nowz; }
	else { _root = root; }
	// ���f����������
	if (nowx > 0) { _direction = CHARA::STATE::RIGHT_DOWN; }
	if (nowx < 0) { _direction = CHARA::STATE::LEFT_UP; }
	if (nowz > 0) { _direction = CHARA::STATE::RIGHT_UP; }
	if (nowz < 0) { _direction = CHARA::STATE::LEFT_DOWN; }
}

void EnemyBase::Process(Game& g)
{
	ObjectBase::Process(g);
}

void EnemyBase::Draw(Game& g)
{
	MV1SetScale(_mh, VGet(MODEL_SIZE, MODEL_SIZE, MODEL_SIZE));

	if (_direction == CHARA::STATE::RIGHT_DOWN) {  // ���L�[(�E���ړ�)
		MV1SetRotationXYZ(_mh, VGet(0.0f, -150.0f * DX_PI_F / 180.0f, 0.0f));
	}
	if (_direction == CHARA::STATE::LEFT_UP) {     // ��L�[(����ړ�)
		MV1SetRotationXYZ(_mh, VGet(0.0f, 30.0f * DX_PI_F / 180.0f, 0.0f));
	}
	if (_direction == CHARA::STATE::RIGHT_UP) {    // �E�L�[(�E��ړ�)
		MV1SetRotationXYZ(_mh, VGet(0.0f, 120.0f * DX_PI_F / 180.0f, 0.0f));
	}
	if (_direction == CHARA::STATE::LEFT_DOWN) {   // ���L�[(�����ړ�)
		MV1SetRotationXYZ(_mh, VGet(0.0f, -60.0f * DX_PI_F / 180.0f, 0.0f));
	}

	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetPosition(_mh, VGet(static_cast<float>(_nowx), static_cast<float>(_nowy), static_cast<float>(_nowz)));
	MV1DrawModel(_mh);
}