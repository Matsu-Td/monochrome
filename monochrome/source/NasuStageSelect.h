#pragma once

/**
 * @file NasuStageSelect.h
 * @brief ステージ選択画面でのプレイヤー(ナス君)移動処理
 *
 * @date 2020-09-20
 * @author 松尾忠彦
 */

#include "Game.h"

class NasuStageSelect
{
public:
	NasuStageSelect();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
	 * ナス君状態,ステージ切替処理
	 * @param g ゲームクラス参照
	 * @param state 状態
	 * @param direction 移動方向
	 * @param nextStage 次のステージ(±指定)
	 */
	void MoveStage(Game& g, int state, int direction, int nextStage);

	/**
	 * ナス君移動、モーション処理
	 * @param moveX X座標移動方向(±指定)
	 * @param moveY Y座標移動方向(±指定)
	 */
	void MoveMotion(int moveX, int moveY);

	/**
	 * 回転移動座標 差分処理
	 */
	void SubPosition();

	/**
	 * 回転移動演出処理
	 */
	void Rotation();

private:
	static constexpr int PLAYER_RIGHT = 1;      // プレイヤー右向き判定
	static constexpr int PLAYER_LEFT = 2;       // プレイヤー左向き判定
	static constexpr int BLOCK_MOVE_X = 73;     // ブロック移動距離(X座標)
	static constexpr int BLOCK_MOVE_Y = 42;     // ブロック移動距離(Y座標)

	static constexpr int GROUND_Y = 853;        // 着地位置
	static constexpr int ROT_CNT_ALL = 60;      // 総回転カウント数
	static constexpr int MOVE_POS_X = 960, MOVE_POS_Y = 325;   // 最終回転移動座標

	int _cg[4];          // 画像
	int _x, _y;          // 座標
	int _oldX, _oldY;    // 1つ前の座標
	int _w, _h;          // 画像サイズ
	int _direction;      // 画像の向き
	int _g;              // 重力加速度
	int	_moveTime;	     // 移動時間
	int _all;            // 総移動時間
	int _state;          // 状態	
	int _rotX, _rotY;    // 回転演出用座標
	float _angle;        // 回転値
	int _subX, _subY;    // 座標 - ステージスライド画像中心座標
	int _rotCnt;         // 回転させるカウント
};
