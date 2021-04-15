/** 
 * @file   Goal.h
 * @brief  �S�[���N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "ObjectBase.h"

/**
 * @brief �S�[���N���X
 */
class Goal:public ObjectBase {
public:
	Goal(Game& g);
	~Goal();
	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::GOAL; }

	void Init(Game& g);
	void Process(Game& g);
	void Draw(Game& g);
	void Damage(Game& g);
	
private:
	static constexpr float MAX_SIZE = 100.0f;  // ���f���̍ő�T�C�Y

	int _rotation;         // ��]
	int _rotSpd;           // ��]���x
	float _sx, _sy, _sz;   // ���f���T�C�Y
	float _sizeUpSpd;      // �T�C�Y�A�b�v���x
	int _gameClearCnt;     // �Q�[���N���A�J�E���g
};