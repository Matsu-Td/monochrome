/** 
 * @file   Camera.h
 * @brief  カメラクラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "DxLib.h"
#include "ObjectBase.h"

/**
 * @brief カメラクラス
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
	VECTOR _cameraPos;         // カメラの設置位置
	int _posX, _posY, _posZ;   // ナス君の座標を格納
};