/** 
 * @file   MelodyTitle.h
 * @brief  タイトル画面獲得音符表示
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "game.h"

/**
 * @brief タイトル画面獲得音符表示
 */
class MelodyTitle{
public:
	MelodyTitle();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

private:
	static constexpr float ALPHA_MAX = 255.0f;   // α最大値
	static constexpr float ALPHA_MIN = 0.0f;     // α最小値
	static constexpr int MELODY_ALL = 6;         // メロディのかけら総数
	const int X[MELODY_ALL] = { 250,350,450,550,640,700 };   // メロディのかけらX座標
	const int Y[MELODY_ALL] = { 100,122,145,148,115,60 };    // メロディのかけらY座標
	const float ROT[MELODY_ALL] = { 20.0f,20.0f,18.0f,0.0f,-20.0f,-45.0f };  // メロディのかけら回転値

	int _cgMelody[2];     // メロディのかけら
	int _cgGosenhu;       // 五線譜

	int _w[2];            // 画像サイズ(横幅)
	int _h;               // 画像サイズ(縦幅)
	float _melodyAlpha;   // メロディのかけらαブレンド
	int _alphaSwitch;     // メロディのかけらαブレンド増減切替
};