#pragma once

/**
 * @file Camera.h
 * @brief カメラ処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
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
	VECTOR _cameraPos;         // カメラの設置位置
	int _posX, _posY, _posZ;   // ナス君の座標を格納
};