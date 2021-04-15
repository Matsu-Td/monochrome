/** 
 * @file   ModeStageSelect.h
 * @brief  ステージセレクトモードクラス
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"
#include "StageSlide.h"
#include "NasuStageSelect.h"
#include "KyuriStageSelect.h"
#include "StageSyosai.h"

/**
 * @brief ステージセレクトモードクラス
 */
class ModeStageSelect : public ModeBase{
	using base = ModeBase;

public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:
	static constexpr int PIANO_ALL = 6;                          // ピアノブロック総数
	const int PIANO_X[PIANO_ALL] = { 656,802,948,729,875,1021 }; // ピアノブロックX座標
	const int PIANO_Y[2] = { 860,902 };                          // ピアノブロックY座標
	static constexpr int MODORU_X = 40,   MODORU_Y = 960;        // 「もどる」表示座標
	static constexpr int KETTEI_X = 1640, KETTEI_Y = 960;        // 「けってい」表示座標
	static constexpr int MSMS_X = 1550;       // サイト名表示X座標
	const int MSMS_Y[2] = { 10,60 };          // サイト名表示Y座標

	int	_bg;               // 背景
	int _cgPiano[2]; 	   // ピアノブロック
	int	_cgModoru;	       // もどるUI
	int	_cgKettei;	  	   // けっていUI
	int _cgMsms[2];        // BGM08著作権元のサイト名

	NasuStageSelect _nasuStageSelect;
	KyuriStageSelect _kyuriStageSelect;
	StageSlide _stageSlide;
	StageSyosai _stageSyosai;
};