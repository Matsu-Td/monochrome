#pragma once

/**
 * @file Camera.h
 * @brief �J��������
 *
 * @date 2020-09-24
 * @author �������F
 */

#include "DxLib.h"
#include "ObjectBase.h"

class Camera : public ObjectBase {
public:
	Camera();
	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::CAMERA; }

	void Init();
	void Process(Game& g);

	void Position(int x, int y, int z) {
		_posX = x;
		_posY = y;
		_posZ = z;
	}

private:
	VECTOR _cameraPos;         // �J�����̐ݒu�ʒu
	int _posX, _posY, _posZ;   // �i�X�N�̍��W���i�[
};