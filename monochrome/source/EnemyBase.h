/** 
 * @file   EnemyBase.h
 * @brief  エネミー(フライパン)基底クラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "ObjectBase.h"

/**
 * @brief エネミー(フライパン)基底クラス
 */
class EnemyBase :public ObjectBase{
public:
	EnemyBase();
	~EnemyBase();

	virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::ENEMYABCD; }

	virtual void Init();
	virtual void Process(Game& g);
	virtual void Draw(Game& g);

	/**
	* 移動ルート処理
	* @param movx,movz 次に進むブロック(移動可、不可を判定)
	* @param nowx,nowz 現在の座標
	* @param root 移動ルート切替
	* @param id マップデータID(ブロックの位置)
	* @param g ゲームクラス参照
	*/
	void MoveRoot(int movx, int movz, int nowx, int nowz, int root, int id, Game& g);

protected:
	static constexpr float MODEL_SIZE = 80.0f;
	int _root;        // 移動ルート
};