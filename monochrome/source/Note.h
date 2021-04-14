#pragma once

/**
 * @file Note.h
 * @brief 音符獲得処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
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
	static constexpr float MAX_SIZE = 100.0f;  // モデルの最大サイズ

	int _mhNote[2];       // モデル
	int _rizeCnt;         // メロディのかけらが上昇するカウント
	int _rotation;        // 回転値
	float _sx, _sy, _sz;  // モデルのサイズ
};