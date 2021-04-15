/** 
 * @file   StageSyosai.h
 * @brief  ステージ詳細表示
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "game.h"

/**
 * @brief ステージ詳細表示クラス
 */
class StageSyosai{
public:
	StageSyosai();

	void Draw(Game& g);

private:
	static constexpr int SYOSAI_X = 680, SYOSAI_Y = 600;  // ステージ詳細表示座標
	static constexpr int BANGO_LX = 100;         // ステージ番号表示X座標(左側)
	static constexpr int BANGO_RX = 1500;        // ステージ番号表示X座標(右側)
	static constexpr int BANGO_Y = 480;          // ステージ番号表示Y座標

	int _cgStageBango[6];   // ステージ番号
	int _cgStageSyosai[6];  // ステージ詳細
};