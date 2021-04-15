/** 
 * @file   Camera.cpp
 * @brief  カメラクラス
 * 
 * @author matsuo tadahiko
 */

#include "Camera.h"
#include "DxLib.h"
#include "game.h"

Camera::Camera()
{
	Init();
}

void Camera::Init()
{
	_cameraPos.x = 0.0f;
	_cameraPos.y = 0.0f;
	_cameraPos.z = 0.0f;

	_posX = 0;
	_posY = 0;
	_posZ = 0;
}

void Camera::Process(Game& g)
{
	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			// プレイヤーの現在の座標を取得
			_nowx = (*ite)->GetNowX();
			_nowy = (*ite)->GetNowY();
			_nowz = (*ite)->GetNowZ();
		}
	}
	_cameraPos.x = _nowx + 200.0f;
	_cameraPos.y = _nowy + 800.0f;
	_cameraPos.z = _nowz - 300.0f;

	SetCameraPositionAndTarget_UpVecY(_cameraPos, VGet(static_cast<float>(_nowx), 0.0f, static_cast<float>(_nowz)));  //プレイヤーの上から見下ろす
}