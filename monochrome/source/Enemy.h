
/**
 * @file Enemy.h
 * @brief �G(�L���E���N)�̈ړ��A�`�揈��
 *
 * @date 2020-09-24
 * @author �������F
 */

#pragma once
#include "ObjectBase.h"
#include "EnemyA.h"
#include "Note.h"
#include <memory>
#include "PianoSound.h"


class Enemy : public ObjectBase {
public:
	Enemy(Game& g);
	~Enemy();
	virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::ENEMY; }

	void Init(Game& g);
	void Process(Game& g);
	void Draw(Game& g);
	void Damage(Game& g);

private:
	static constexpr int MOVE_FLAME = 30;   // �ړ��t���[��	

	int _lateCnt;           // �i�X�N�ɏ����x��Ĉړ�����
	int _plX, _plZ;         // �v���C���[�̃u���b�N�̈ʒu���i�[
	int _oldPlX, _oldPlZ;   // �v���C���[�̈�O�̃u���b�N�ʒu���i�[
	int _oldEnPos;          // ����O�̈ʒu(���K�̘A���Đ��h�~)
	int _disX, _disZ;       // �L���E���N�ƓG�̋���
	float _w;               // �傫��


};