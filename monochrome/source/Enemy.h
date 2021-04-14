
/**
 * @file Enemy.h
 * @brief 敵(キュウリ君)の移動、描画処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#pragma once
#include "ObjectBase.h"
#include "EnemyA.h"
#include "Note.h"
#include <memory>
#include "PianoSound.h"


class Enemy : public ObjectBase {
public:
	Enemy(Game& g);
	~Enemy();
	virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::ENEMY; }

	void Init(Game& g);
	void Process(Game& g);
	void Draw(Game& g);
	void Damage(Game& g);

private:
	static constexpr int MOVE_FLAME = 30;   // 移動フレーム	

	int _lateCnt;           // ナス君に少し遅れて移動する
	int _plX, _plZ;         // プレイヤーのブロックの位置を格納
	int _oldPlX, _oldPlZ;   // プレイヤーの一つ前のブロック位置を格納
	int _oldEnPos;          // 一歩前の位置(音階の連続再生防止)
	int _disX, _disZ;       // キュウリ君と敵の距離
	float _w;               // 大きさ


};