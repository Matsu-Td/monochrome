/**
 * @file   KyuriStageSelect.h
 * @brief  ステージ選択画面の敵(キュウリ君)表示
 * 
 * @author matsuo tadahiko
 * @date   2020/09/20
 */

#pragma once

#include "Game.h"

class KyuriStageSelect
{
public:
	KyuriStageSelect();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
	 * 回転移動演出処理
	 */
	void Rotation();

private:
	static constexpr int GROUND_Y = 700;             // 着地位置
	static constexpr int POS_X = 1400, POS_Y = 653;  // 回転移動演出前座標
	static constexpr int DIF_X = 440, DIF_Y = 328;   // 移動位置との差

	int _cg;           // 画像
	int _x, _y;        // 座標
	int _w, _h;        // 画像サイズ
	int _g;            // 重力加速度
	float _angle;      // 回転値
	int _rotCnt;       // 回転させるカウント
	int _cntAll;       // 総カウント数
};