/** 
 * @file   ModeTitle.h
 * @brief  タイトルモードクラス
 * 
 * @author matsuo tadahiko
 * @author iwamae soma
 */

#include "ModeBase.h"
#include "NasuTitle.h"
#include "MelodyTitle.h"

namespace MODETITLE {
	enum SELECT {
		UNSELECTED, // 未選択の状態
		START,      // メニュー：はじめる
		GAME_END,   // メニュー：おわる
		MELODY,     // メニュー：メロディ
		TUTORIAL,   // メニュー：チュートリアル
	};
}

/**
 * @brief タイトルモードクラス
 */
class ModeTitle : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

	static int _selectMenu;  // 選択しているメニューを格納

private:
	static constexpr int CG_TITLE_X = 480, CG_TITLE_Y = 270;      // タイトル名座標
	static constexpr int CG_KETTEI_X = 1640, CG_KETTEI_Y = 960;   // けってい画像座標
	static constexpr int CG_SSGID_X = 1560, CG_SSGID_Y = 50;      // 操作ガイド座標

	static constexpr int CG_PIANO_ALL = 12;   // ピアノブロック表示総数
	const int CG_PIANO_X[CG_PIANO_ALL] = { 664,810,956,1102,518,591,664,737,810,883,956,1029 };  // ピアノブロックX座標
	const int CG_PIANO_Y[CG_PIANO_ALL] = { 603,687,771,855,603,645,687,729,771,813,855,897 };    // ピアノブロックY座標

	static constexpr int UI_ALL = 4;                  // UI(メニュー)総数
	const int UI_POS_Y[UI_ALL] = { 470,550,630,630 }; // UI(メニュー)Y座標

	int _bg;           // 背景

	int	_cgTitle;	   // タイトル名
	int _cgKettei;     // けってい
	int _cgUi[UI_ALL]; // UI(メニュー)
	int _cgSsgid;      // 操作ガイド
	int _cgPiano[3];   // ピアノブロック

	int _uix[4] = { 740,900,1040,1150 };  // メニュー選択用UIのx座標
	int _uiy[4] = { 470,550,630,630 };    // メニュー選択用UIのy座標
	int _sinCnt;            // 垂直アニメーション用カウント

	NasuTitle _nasuTitle;
	MelodyTitle _melodyTitle;
};