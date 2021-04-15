/** 
 * @file   NasuTitle.h
 * @brief  タイトル画面のプレイヤー移動処理
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "Game.h"

/**
 * @brief タイトル画面のプレイヤー(ナス)クラス
 */
class NasuTitle{
public:
	NasuTitle();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
	 * ナス君移動、モーション処理
	 * @param moveX X座標移動方向(±指定)
	 * @param moveY Y座標移動方向(±指定)
	 */
	void MoveMotion(int moveX, int moveY);

private:
	const int PLAYER_RIGHT = 1;    // プレイヤー右向き判定
	const int PLAYER_LEFT = -1;    // プレイヤー左向き判定
	const int BLOCK_MOVE_X = 73;   // ブロック移動距離(X座標)
	const int BLOCK_MOVE_Y = 42;   // ブロック移動距離(Y座標)
	const int GROUND_Y = 530;      // 着地位置

	int _cg[4];       // 画像
	int _x, _y;       // 座標
	int _oldX, _oldY; // 1つ前の座標
	int _g;           // 重力加速度
	int _direction;   // 向き
	int	_moveTime;	  // 移動時間
	int _moveAll;     // 総移動時間
	int _state;       // 状態
};