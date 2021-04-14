#pragma once

/**
 * @file EnemyBase.h
 * @brief �G(�t���C�p��)�p�x�[�X�N���X
 *
 * @date 2020-09-24
 * @author �������F
 */


#include "ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	~EnemyBase();
	virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::ENEMYABCD; }
	virtual void Init();
	virtual void Process(Game& g);
	virtual void Draw(Game& g);

	/**
	* �ړ����[�g����
	* @param movx,movz ���ɐi�ރu���b�N(�ړ��A�s�𔻒�)
	* @param nowx,nowz ���݂̍��W
	* @param root �ړ����[�g�ؑ�
	* @param id �}�b�v�f�[�^ID(�u���b�N�̈ʒu)
	* @param g �Q�[���N���X�Q��
	*/
	void MoveRoot(int movx, int movz, int nowx, int nowz, int root, int id, Game& g);

protected:
	static constexpr float MODEL_SIZE = 80.0f;
	int _root;        // �ړ����[�g
};