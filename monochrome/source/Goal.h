#pragma once

/**
 * @file Goal.h
 * @brief ゴール発生処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "ObjectBase.h"

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
	static constexpr float MAX_SIZE = 100.0f;  // モデルの最大サイズ

	int _rotation;         // 回転
	int _rotSpd;           // 回転速度
	float _sx, _sy, _sz;   // モデルサイズ
	float _sizeUpSpd;      // サイズアップ速度
	int _gameClearCnt;     // ゲームクリアカウント
};