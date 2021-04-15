/** 
 * @file   ModeGameClear.cpp
 * @brief  ゲームクリアモードクラス
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
#include "Mode_CrossFade.h"

bool ModeGameClear::Initialize(Game& g) 
{
	if (!base::Initialize(g)) { return false; }

	_cgGameClear = ResourceServer::LoadGraph("res/gameclear.png");

	_mode = 0;

	return true;
}

bool ModeGameClear::Terminate(Game& g)
{
	base::Terminate(g);
	return true;
}

bool ModeGameClear::Process(Game& g) 
{
	base::Process(g);

	if (_mode == 1) {
		g._serverMode->Del(this);
		g._serverMode->Del(g._serverMode->Get("Game"));

		ModeTitle* modeTitle = new ModeTitle();
		g._serverMode->Add(modeTitle, 0, "Title");                // タイトル画面追加
	}

	if (_mode == 2) {
		g._serverMode->Del(this);
		g._serverMode->Del(g._serverMode->Get("Game"));

		ModeStageSelect* modeStageSelect = new ModeStageSelect();
		g._serverMode->Add(modeStageSelect, 0, "StageSelect");    // ステージ選択画面追加
	}

	if (g._gTrg & PAD_INPUT_A){
		PlaySoundMem(g._se["modoru"], DX_PLAYTYPE_BACK);
		StopSoundMem(g._se["clear"]);

		_mode = 1;
		Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
		md->Capture(30);
		g._serverMode->Add(md, 99999, "CrossFade");              // クロスフィード追加
	}

	if (g._gTrg & PAD_INPUT_B) {
		PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);
		StopSoundMem(g._se["clear"]);

		_mode = 2;
		Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
		md->Capture(30);
		g._serverMode->Add(md, 99999, "CrossFade");              // クロスフィード追加
	}       

	return true;
}

bool ModeGameClear::Draw(Game& g)
{
	base::Draw(g);

	DrawGraph(0, 0, _cgGameClear, FALSE);

	return true;
}