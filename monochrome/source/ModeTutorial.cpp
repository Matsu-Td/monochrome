
/**
 * @file ModeTutorial.cpp
 * @brief チュートリアル
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"
#include "ModeTutorial.h"
#include "Mode_CrossFade.h"
#include "ModeGame.h"
#include "ModeTitle.h"


bool ModeTutorial::Initialize(Game& g) {
	if (!base::Initialize(g)) { return false; }

	_cg[0] = ResourceServer::LoadGraph("res/setsumei1.png");
	_cg[1] = ResourceServer::LoadGraph("res/setsumei2.png");
	_cg[2] = ResourceServer::LoadGraph("res/setsumei3.png");
	_cg[3] = ResourceServer::LoadGraph("res/setsumei4.png");
	_cg[4] = ResourceServer::LoadGraph("res/setsumei5.png");
	_cg[5] = ResourceServer::LoadGraph("res/setsumei6.png");
	_cg[6] = ResourceServer::LoadGraph("res/setsumei7.png");
	_cg[7] = ResourceServer::LoadGraph("res/setsumei8.png");
	_cg[8] = ResourceServer::LoadGraph("res/setsumei9.png");
	_cg[9] = ResourceServer::LoadGraph("res/setsumei10.png");

	_mode = 0;
	_cgNum = 0;
	g._gStageNo = 0;
	_modeCnt = 40;

	return true;
}

bool ModeTutorial::Terminate(Game& g) {
	base::Terminate(g);
	return true;
}

bool ModeTutorial::Process(Game& g) {
	base::Process(g);

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	if (_cgNum == 6 && g._gTrg & PAD_INPUT_B) {   // 説明画面1～7表示⇒ステージへ
		// ゲームモードのオブジェクト処理をスタート
		modeGame->_stopObjProcess = false;
		_cgNum = 7;
	}

	if (g._gHasKyuri == true) {                   // キュウリ君捕まえる⇒説明画面8表示
		--_modeCnt;
		if (_modeCnt == 0) {
			_modeCnt = 0;
			modeGame->_stopObjProcess = true;
		}
	}

	if (_cgNum == 8 && g._gTrg & PAD_INPUT_B) {   // 説明画面8,9表示⇒ステージへ
		// ゲームモードのオブジェクト処理をスタート
		modeGame->_stopObjProcess = false;
		_cgNum = 9;
	}

	if (_mode == 1) {
		g._serverMode->Del(this);
		g._serverMode->Del(g._serverMode->Get("Game"));

		ModeTitle* modeTitle = new ModeTitle();
		g._serverMode->Add(modeTitle, 0, "Title");
	}

	if (_cgNum == 9 && g._gTrg & PAD_INPUT_B && modeGame->_stopObjProcess == true) {
		PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);
		StopSoundMem(g._se["clear"]);
		_mode = 1;
		Mode_Overlay_CrossFade* md = new Mode_Overlay_CrossFade();
		md->Capture(30);
		g._serverMode->Add(md, 99999, "CrossFade");
	}

	if (g._gTrg & PAD_INPUT_B && modeGame->_stopObjProcess == true) {
		PlaySoundMem(g._se["kettei"], DX_PLAYTYPE_BACK);
		++_cgNum;
	}

	return true;
}

bool ModeTutorial::Draw(Game& g) {
	base::Draw(g);
	
	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");
	// ゲームモードのオブジェクト処理がストップの状態のとき描画を行う
	if (modeGame->_stopObjProcess == true) {
		DrawGraph(CG_X, CG_Y, _cg[_cgNum], FALSE);
	}

	return true;
}