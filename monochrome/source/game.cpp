/** 
 * @file   game.cpp
 * @brief  ゲーム本体
 * 
 * @author matsuo tadahiko
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"
#include "ModeTitle.h"
#include "ModeAmgLogo.h"

Game::Game() :_gkey(0), _gTrg(0), _gFrameCount(0), _gStageNo(1), _gHasKyuri(false), _gHasLanding(false), _gHasGameEnd(false), _gMelodyTotal(0)
{
	//音階SE
	_se["do"] = ResourceServer::LoadSoundMem("res/sound/SE_do.mp3");        //「ド」の音をロード
	_se["re"] = ResourceServer::LoadSoundMem("res/sound/SE_re.mp3");        //「レ」の音をロード
	_se["mi"] = ResourceServer::LoadSoundMem("res/sound/SE_mi.mp3");        //「ミ」の音をロード
	_se["fa"] = ResourceServer::LoadSoundMem("res/sound/SE_fa.mp3");        //「ファ」の音をロード
	_se["so"] = ResourceServer::LoadSoundMem("res/sound/SE_so.mp3");        //「ソ」の音をロード
	_se["ra"] = ResourceServer::LoadSoundMem("res/sound/SE_ra.mp3");        //「ラ」の音をロード
	_se["si"] = ResourceServer::LoadSoundMem("res/sound/SE_si.mp3");        //「シ」の音をロード
	_se["do_1"] = ResourceServer::LoadSoundMem("res/sound/SE_do_1oku.mp3"); //「ドの1オクターブ上」の音をロード
	_se["re_1"] = ResourceServer::LoadSoundMem("res/sound/SE_re_1oku.mp3"); //「レの1オクターブ上」の音をロード
	_se["mi_1"] = ResourceServer::LoadSoundMem("res/sound/SE_mi_1oku.mp3"); //「ミの1オクターブ上」の音をロード
	_se["fa_1"] = ResourceServer::LoadSoundMem("res/sound/SE_fa_1oku.mp3"); //「ファの1オクターブ上」の音をロード
	_se["so_1"] = ResourceServer::LoadSoundMem("res/sound/SE_so_1oku.mp3"); //「ソの1オクターブ上」の音をロード
	_se["ra_1"] = ResourceServer::LoadSoundMem("res/sound/SE_ra_1oku.mp3"); //「ラの1オクターブ上」の音をロード
	_se["si_1"] = ResourceServer::LoadSoundMem("res/sound/SE_si_1oku.mp3"); //「シの1オクターブ上」の音をロード
	_se["do_2"] = ResourceServer::LoadSoundMem("res/sound/SE_do_2oku.mp3"); //「ドの2オクターブ上」の音をロード

	//その他SE
	_se["nyuusyu"] = ResourceServer::LoadSoundMem("res/sound/SE_nyuusyu.mp3");  // キュウリ君獲得音
	_se["clear"]   = ResourceServer::LoadSoundMem("res/sound/SE_clear.mp3");    // クリア音
	_se["over"]    = ResourceServer::LoadSoundMem("res/sound/SE_over.mp3");     // オーバー音
	_se["yakeru"]  = ResourceServer::LoadSoundMem("res/sound/SE_yakeru.mp3");   // 敵との接触音
	_se["kettei"]  = ResourceServer::LoadSoundMem("res/sound/SE_kettei.mp3");   // 決定
	_se["modoru"]  = ResourceServer::LoadSoundMem("res/sound/SE_modoru.mp3");   // キャンセル、戻る
	_se["sentaku"] = ResourceServer::LoadSoundMem("res/sound/SE_sentaku.mp3");  // ステージ選択
	_se["slide1"]  = ResourceServer::LoadSoundMem("res/sound/SE_slide1.mp3");   // ステージ選択スライド音
	_se["slide2"]  = ResourceServer::LoadSoundMem("res/sound/SE_slide2.mp3");   // ステージ選択スライド禁止音

	_se["bgm08"] = ResourceServer::LoadSoundMem("res/sound/BGM08.mp3");         // ゴール出現後のBGM
	ChangeVolumeSoundMem(180, _se["bgm08"]);

	_serverMode = new ModeServer(*this);

	ModeAmgLogo* modeAmgLogo = new ModeAmgLogo();
	_serverMode->Add(modeAmgLogo, 0, "AmgLogo");
}

Game::~Game()
{
	delete _serverMode;
	delete _mapChips;
}

void Game::Input()
{
	int keyold = _gkey;
	_gkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gkey ^ keyold) & _gkey; 
}

void Game::Process()
{
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();

	_gFrameCount++;
}

void Game::Draw()
{
	_serverMode->DrawInit();
	_serverMode->Draw();
	_serverMode->DrawFinish();
}