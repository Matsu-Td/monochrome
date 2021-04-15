/** 
 * @file   ModeStageSelect.cpp
 * @brief  ステージセレクトモードクラス
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeGameClear.h"
#include "ModeStageSelect.h"
#include "ModeGame.h"
#include "Mode_CrossFade.h"
#include "Mode_LightMap.h"

bool ModeStageSelect::Initialize(Game& g) {
	if (!base::Initialize(g)) { return false; }

	_bg = ResourceServer::LoadGraph("res/stagesentakuhaikei.png");

	_cgPiano[0] = ResourceServer::LoadGraph("res/piano2-kuro.png");
	_cgPiano[1] = ResourceServer::LoadGraph("res/piano1-kuro.png");

	_cgModoru = ResourceServer::LoadGraph("res/modoru.png");
	_cgKettei = ResourceServer::LoadGraph("res/kettei.png");

	_cgMsms[0] = ResourceServer::LoadGraph("res/musmus1.png");
	_cgMsms[1] = ResourceServer::LoadGraph("res/musmus2.png");

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
	g._gStageNo = 1;

	return true;
}

bool ModeStageSelect::Terminate(Game& g) 
{
	base::Terminate(g);

	return true;
}

bool ModeStageSelect::Process(Game& g)
{
	base::Process(g);

	--_modeCnt;
	if (_modeCnt <= 0) { _modeCnt = 0; }

	_nasuStageSelect.Process(g);
	_kyuriStageSelect.Process(g);
	_stageSlide.Process(g);

	// ナス＆キュウリ回転演出
	if (_mode == 0) {
		_nasuStageSelect.SubPosition();
	}
	 if (_mode == 2) {
		 _nasuStageSelect.Rotation();
		 _kyuriStageSelect.Rotation();
	 }

	 // モード切替
	if (_mode == 1) { 
		g._serverMode->Del(this);

		ModeTitle* modeTitle = new ModeTitle();
		g._serverMode->Add(modeTitle, 0, "Title");
	}

	if (g._gTrg& PAD_INPUT_A && _modeCnt == 0 && _mode == 0) {
		PlaySoundMem(g._se["modoru"], DX_PLAYTYPE_BACK);
		_mode = 1;

		Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
		md->Capture(30);
		g._serverMode->Add(md, 99999, "CrossFade");             // クロスフィード追加
	}

	if (g._gTrg & PAD_INPUT_B && _modeCnt == 0 && _mode == 0) {
		_mode = 2;
		StopMusic();
		PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);
		PlaySoundMem(g._se["sentaku"], DX_PLAYTYPE_BACK);

		Mode_LightMap* mode_lightmap = new Mode_LightMap();
		g._serverMode->Add(mode_lightmap, 99999, "LightMap");  // ライトマップ(暗転)追加
	}       

	return true;
}

bool ModeStageSelect::Draw(Game& g) {
	base::Draw(g);

	DrawGraph(0, 0, _bg, FALSE);

	for (int i = 0; i < PIANO_ALL; i++) {     // ピアノブロック配置
		DrawGraph(PIANO_X[i], PIANO_Y[i / 3], _cgPiano[i / 3], TRUE);
	}

	DrawGraph(MSMS_X, MSMS_Y[0], _cgMsms[0], TRUE);
	DrawGraph(MSMS_X, MSMS_Y[1], _cgMsms[1], TRUE);

	DrawGraph(MODORU_X, MODORU_Y, _cgModoru, TRUE);
	DrawGraph(KETTEI_X, KETTEI_Y, _cgKettei, TRUE);

	_stageSyosai.Draw(g);
	_stageSlide.Draw(g);
	_kyuriStageSelect.Draw(g);
	_nasuStageSelect.Draw(g);

	return true;
}