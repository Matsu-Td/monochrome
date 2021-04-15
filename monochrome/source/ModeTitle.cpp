/** 
 * @file   ModeTitle.cpp
 * @brief  タイトルモードクラス
 * 
 * @author matsuo tadahiko
 * @author iwamae soma
 */

#include "DxLib.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeStageSelect.h"
#include "Mode_CrossFade.h"
#include "ModeMelody.h"
#include "ModeTutorial.h"
#define _USE_MATH_DEFINES
#include <math.h>

int ModeTitle::_selectMenu = MODETITLE::SELECT::UNSELECTED;

bool ModeTitle::Initialize(Game& g) {
	if (!base::Initialize(g)) { return false; }

	_bg = ResourceServer::LoadGraph("res/haikeihaiiro.png");
	_cgTitle = ResourceServer::LoadGraph("res/title.png");

	_cgKettei = ResourceServer::LoadGraph("res/kettei.png");

	_cgPiano[0] = ResourceServer::LoadGraph("res/piano2-kuro.png");
	_cgPiano[1] = ResourceServer::LoadGraph("res/piano1-kuro.png");

	_cgUi[0] = ResourceServer::LoadGraph("res/hazimeru.png");
	_cgUi[1] = ResourceServer::LoadGraph("res/owaru.png");
	_cgUi[2] = ResourceServer::LoadGraph("res/melody.png");
	_cgUi[3] = ResourceServer::LoadGraph("res/tutorial.png");

	_cgSsgid = ResourceServer::LoadGraph("res/ssgid.PNG"); 

	switch (g._gMelodyTotal) {
	case 0:
		PlayMusic("res/sound/BGM00.mp3", DX_PLAYTYPE_LOOP); break;
	case 1:
		PlayMusic("res/sound/BGM01.mp3", DX_PLAYTYPE_LOOP); break;
	case 2:
		PlayMusic("res/sound/BGM02.mp3", DX_PLAYTYPE_LOOP); break;
	case 3:
		PlayMusic("res/sound/BGM03.mp3", DX_PLAYTYPE_LOOP); break;
	case 4:
		PlayMusic("res/sound/BGM04.mp3", DX_PLAYTYPE_LOOP); break;
	case 5:
		PlayMusic("res/sound/BGM05.mp3", DX_PLAYTYPE_LOOP); break;
	case 6:
		PlayMusic("res/sound/BGM06.mp3", DX_PLAYTYPE_LOOP); break;
	}

	_mode = 0;
	_modeCnt = 30;
	_sinCnt = 0;

	return true;
}

bool ModeTitle::Terminate(Game& g) {
	base::Terminate(g);
	return true;
}

bool ModeTitle::Process(Game& g) {
	base::Process(g);

	--_modeCnt;
	if (_modeCnt <= 0) { _modeCnt = 0; }
	
	_nasuTitle.Process(g);
	_melodyTitle.Process(g);

	if (_mode == 1) {  
		g._serverMode->Del(this);

		ModeStageSelect* modeStageSelect = new ModeStageSelect();
		g._serverMode->Add(modeStageSelect, 0, "StageSelect");   // ステージ選択画面追加
	}

	if (_mode == 2) {
		g._serverMode->Del(this);

		ModeMelody* modeMelody = new ModeMelody();
		g._serverMode->Add(modeMelody, 0, "Melody");             // メロディ画面追加
	}

	if (_mode == 3) {
		g._serverMode->Del(this);

		ModeTutorial* modeTutorial = new ModeTutorial();
		g._serverMode->Add(modeTutorial, 10, "Tutorial");        // チュートリアル追加

		ModeGame* modeGame = new ModeGame();
		g._serverMode->Add(modeGame, 0, "Game");                 // ゲーム追加
	}

	if (_selectMenu == MODETITLE::SELECT::START) {
		if (g._gTrg & PAD_INPUT_B && _modeCnt == 0) {
			PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);

			_mode = 1;
			Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
			md->Capture(30);
			g._serverMode->Add(md, 99999, "CrossFade");         // クロスフィード追加
		}
	}
	else if (_selectMenu == MODETITLE::SELECT::GAME_END) {
		if (g._gTrg & PAD_INPUT_B) {
			g._gHasGameEnd = true;                              // ゲーム終了フラグ
		}
	}
	else if (_selectMenu == MODETITLE::SELECT::MELODY) {
		if (g._gTrg & PAD_INPUT_B) {          
			PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);

			_mode = 2;
			Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
			md->Capture(30);
			g._serverMode->Add(md, 99999, "CrossFade");         // クロスフィード追加
		}
	}
	else if (_selectMenu == MODETITLE::SELECT::TUTORIAL) {
		if (g._gTrg & PAD_INPUT_B) { 
			PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);

			_mode = 3;
			Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
			md->Capture(30);
			g._serverMode->Add(md, 99999, "CrossFade");       // クロスフィード追加
		}
	}

	//メニュー選択していないときUI画像を垂直にアニメーションさせる
	++_sinCnt;
	if (_selectMenu != MODETITLE::SELECT::START) {_uiy[0] = static_cast<int>(UI_POS_Y[0] - sin(M_PI / 60 * _sinCnt) * 30); }
	else{ _uiy[0] = UI_POS_Y[0]; }
	if (_selectMenu != MODETITLE::SELECT::GAME_END) {_uiy[1] = static_cast<int>(UI_POS_Y[1] - sin(M_PI / 60 * (static_cast<double>(_sinCnt) + 30)) * 30); }
	else{ _uiy[1] = UI_POS_Y[1]; }
	if (_selectMenu != MODETITLE::SELECT::MELODY) {_uiy[2] = static_cast<int>(UI_POS_Y[2] - sin(M_PI / 60 * (static_cast<double>(_sinCnt) + 60)) * 30); }
	else{ _uiy[2] = UI_POS_Y[2]; }
	if (_selectMenu != MODETITLE::SELECT::TUTORIAL) { _uiy[3] = static_cast<int>(UI_POS_Y[3] - sin(M_PI / 60 * (static_cast<double>(_sinCnt) + 90)) * 30); }
	else{ _uiy[3] = UI_POS_Y[3]; }

	return true;
}

bool ModeTitle::Draw(Game& g) {
	base::Draw(g);

	DrawGraph(0, 0, _bg, FALSE);
	DrawGraph(CG_TITLE_X, CG_TITLE_Y, _cgTitle, TRUE);
	DrawGraph(CG_KETTEI_X, CG_KETTEI_Y, _cgKettei, TRUE);

	for (int i = 0; i < 4; i++) {
		DrawGraph(CG_PIANO_X[i], CG_PIANO_Y[i], _cgPiano[0], TRUE);
	}
	for (int i = 4; i < CG_PIANO_ALL; i++) {
		DrawGraph(CG_PIANO_X[i], CG_PIANO_Y[i], _cgPiano[i % 2], TRUE);
	}

	for (int i = 0; i < UI_ALL; i++) {
		DrawGraph(_uix[i], _uiy[i], _cgUi[i], TRUE);
	}

	DrawGraph(CG_SSGID_X, CG_SSGID_Y, _cgSsgid, TRUE);

	_nasuTitle.Draw(g);
	_melodyTitle.Draw(g);

	return true;
}
