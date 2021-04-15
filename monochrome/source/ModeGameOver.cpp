/** 
 * @file   ModeGameOver.cpp
 * @brief  ゲームオーバークラス
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "Mode_CrossFade.h"

bool ModeGameOver::Initialize(Game& g) {
	if (!base::Initialize(g)) { return false; }

	_cgGameOver = ResourceServer::LoadGraph("res/gameover.png");

	_mode = 0;

	return true;
}

bool ModeGameOver::Terminate(Game& g) {
	base::Terminate(g);
	return true;
}

bool ModeGameOver::Process(Game& g) {
	base::Process(g);

	if (_mode == 1) {
		g._serverMode->Del(this);
		g._serverMode->Del(g._serverMode->Get("Game"));

		ModeTitle* modeTitle = new ModeTitle();       
		g._serverMode->Add(modeTitle, 0, "Title");                  // タイトル画面追加
	}

	if (g._gTrg & PAD_INPUT_A){
		StopSoundMem(g._se["over"]);
		PlaySoundMem(g._se["modoru"], DX_PLAYTYPE_BACK);

		_mode = 1;
		Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
		md->Capture(30);
		g._serverMode->Add(md, 99999, "CrossFade");                // クロスフィード追加
	} 

	if (g._gTrg & PAD_INPUT_B) {
		StopSoundMem(g._se["over"]);
		PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);

		g._serverMode->Del(this);
		g._serverMode->Del(g._serverMode->Get("Game"));

		ModeGame* modeGame = new ModeGame();  
		g._serverMode->Add(modeGame, 0, "Game");                  // ゲーム画面追加(リトライ)
	}       

	return true;
}

bool ModeGameOver::Draw(Game& g) {
	base::Draw(g);

	DrawGraph(0, 0, _cgGameOver, FALSE);

	return true;
}