/** 
 * @file   Note.h
 * @brief  音符クラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "ObjectBase.h"
#include "DxLib.h"

/**
 * @brief 音符クラス
 */
class Note :public ObjectBase {
public:
	Note(Game& g);
	~Note();

	OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::NOTE; }
	
	void Init();
	void Process(Game& g);
	void Draw(Game& g);

private:
	static constexpr float MAX_SIZE = 100.0f;  // モデルの最大サイズ

	int _mhNote[2];       // モデル
	int _rizeCnt;         // メロディのかけらが上昇するカウント
	int _rotation;        // 回転値
	float _sx, _sy, _sz;  // モデルのサイズ
};