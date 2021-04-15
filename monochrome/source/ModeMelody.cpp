/** 
 * @file   ModeMelody.cpp
 * @brief  メロディーモードクラス
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "ModeTitle.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeMelody.h"
#include "Mode_CrossFade.h"
#define _USE_MATH_DEFINES
#include <math.h>

bool ModeMelody::Initialize(Game& g) {
	if (!base::Initialize(g)) { return false; }

	_bg = ResourceServer::LoadGraph("res/haikeihaiiro.png");

	_cgModoru = ResourceServer::LoadGraph("res/modoru.png");

	_cgPiano[0] = ResourceServer::LoadGraph("res/piano2-kuro.png");
	_cgPiano[1] = ResourceServer::LoadGraph("res/piano1-kuro.png");
	_cgPiano[2] = ResourceServer::LoadGraph("res/piano2-shiro-sakasa.png");
	_cgPiano[3] = ResourceServer::LoadGraph("res/piano1-shiro-sakasa.png");

	_cgNasu[0] = ResourceServer::LoadGraph("res/nasutachie.png");
	_cgNasu[1] = ResourceServer::LoadGraph("res/nasuidou_1.png");
	_cgNasu[2] = ResourceServer::LoadGraph("res/nasuidou_2.png");
	_cgNasu[3] = ResourceServer::LoadGraph("res/nasuidou_3.png");

	_cgMelody[0] = ResourceServer::LoadGraph("res/sibuonpu.png");
	_cgMelody[1] = ResourceServer::LoadGraph("res/hatibuonpu.png");

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
	_x = 373;
	_y = -125;
	_sinCnt = 0;
	_g = 0;
	_cgNum = 0;
	return true;
}

bool ModeMelody::Terminate(Game& g) {
	base::Terminate(g);
	return true;
}

bool ModeMelody::Process(Game& g) {
	base::Process(g);
	
	//ナス君落下処理
	++_g;
	_y += _g;
	if (_y >= GROUND_Y) {
		_y = GROUND_Y;
		++_cgNum;
	}
	
	//メロディのかけら垂直アニメーション
	++_sinCnt;
	for (int i = 0; i < MELODY_TOTALNO; i++) {
		_mely[i] = static_cast<int>(INITIAL_POS - sin(M_PI / MELODY_ANIM_SPD[i] * _sinCnt) * VERTICAL_WIDTH);
	}

	if (_mode == 1) {
		g._serverMode->Del(this);

		ModeTitle* modeTitle = new ModeTitle();                 //タイトル画面へ移動
		g._serverMode->Add(modeTitle, 0, "Title");
	}
	if (g._gTrg & PAD_INPUT_A) 
	{
		PlaySoundMem(g._se["modoru"], DX_PLAYTYPE_BACK);

		_mode = 1;
		Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
		md->Capture(30);
		g._serverMode->Add(md, 99999, "CrossFade");
	}

	return true;
}

bool ModeMelody::Draw(Game& g) {
	base::Draw(g);

	DrawGraph(0, 0, _bg, FALSE);

	DrawGraph(MODORU_POS_X, MODORU_POS_Y, _cgModoru, TRUE);

	for (int i = 0; i < 7; i++) {                   // ピアノブロック表示(4種類)
		if (i <= 3) {DrawGraph(PIANO_POS_X[i], PIANO_POS_Y, _cgPiano[i], TRUE);}
		else { DrawGraph(PIANO_POS_X[i], PIANO_POS_Y, _cgPiano[i - 4], TRUE); }
	}

	for (int i = 0; i < MELODY_TOTALNO; i++) {      // 入手したメロディのかけら表示
		if (g._gMelodyTotal >= i + 1) { DrawGraph(_melx[i], _mely[i], _cgMelody[i % 2], TRUE); }
	}

	DrawGraph(_x, _y, _cgNasu[(_cgNum / 10) % 4], true);

	return true;
}