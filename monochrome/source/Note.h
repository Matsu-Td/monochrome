#pragma once

/**
 * @file Note.h
 * @brief �����l������
 *
 * @date 2020-09-24
 * @author �������F
 */

#include "ObjectBase.h"
#include "DxLib.h"

class Note :public ObjectBase {
public:
	Note(Game& g);
	~Note();
	virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::NOTE; }
	void Init();
	void Process(Game& g);
	void Draw(Game& g);

private:
	static constexpr float MAX_SIZE = 100.0f;  // ���f���̍ő�T�C�Y

	int _mhNote[2];       // ���f��
	int _rizeCnt;         // �����f�B�̂����炪�㏸����J�E���g
	int _rotation;        // ��]�l
	float _sx, _sy, _sz;  // ���f���̃T�C�Y
};