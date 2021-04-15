/** 
 * @file   Camera.h
 * @brief  �J�����N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "DxLib.h"
#include "ObjectBase.h"

/**
 * @brief �J�����N���X
 */
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