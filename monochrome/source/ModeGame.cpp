/**
 * @file ModeGame.cpp
 * @brief ゲームモード
 *
 * @date 2020-09-20
 * @author 松尾忠彦 
 */

#include "DxLib.h"
#include "ModeGame.h"
#include "game.h"
#include "ResourceServer.h"
#include "ModeGameOver.h"

int ModeGame::_steps;

/**
 * 初期化
 */
bool ModeGame::Initialize(Game& g) 
{
	if (!base::Initialize(g)) { return false; }

    g._gHasKyuri = false;
	g._gHasLanding = false;

	// JSONファイル指定、歩数設定
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL: 
		g._mapChips = new MapChips("res/stage2-2/", "stage2-2");
		_steps = STEPS_TUTORIAL;
		break;
	case GAME::STAGENO::ST1_1:
		g._mapChips = new MapChips("res/stage1-1/", "stage1-1"); 
		_steps = STEPS1_1;
		break;
	case GAME::STAGENO::ST1_2:
		g._mapChips = new MapChips("res/stage1-2/", "stage1-2");
		_steps = STEPS1_2;
		break;
	case GAME::STAGENO::ST1_3:
		g._mapChips = new MapChips("res/stage1-3/", "stage1-3"); 
		_steps = STEPS1_3;
		break;
	case GAME::STAGENO::ST2_1:
		g._mapChips = new MapChips("res/stage2-1/", "stage2-1"); 
		_steps = STEPS2_1;
		break;
	case GAME::STAGENO::ST2_2:
		g._mapChips = new MapChips("res/stage2-2/", "stage2-2"); 
		_steps = STEPS2_2;
		break;
	case GAME::STAGENO::ST2_3:
		g._mapChips = new MapChips("res/stage2-3/", "stage2-3"); 
		_steps = STEPS2_3;
		break;
	}

	// JSONマップデータ1次元配列をキャラ移動用に2次元配列に変換
	int k = 0;
	for (int i = 0; i < g._mapChips->_mapSizeZ; i++) {
		for (int j = 0; j < g._mapChips->_mapSizeX; j++) {
			g._gCharaMap[i][j] = g._mapChips->_mapData[k];
			k++;
		}
	}

	_cg[0] = ResourceServer::LoadGraph("res/nokori.png"); 
	_cg[1] = ResourceServer::LoadGraph("res/AHSkani.png"); 
	_cg[2] = ResourceServer::LoadGraph("res/ssgid.PNG"); 

	_cgSteps[0] = ResourceServer::LoadGraph("res/suuji0.png");
	_cgSteps[1] = ResourceServer::LoadGraph("res/suuji1.png");
	_cgSteps[2] = ResourceServer::LoadGraph("res/suuji2.png");
	_cgSteps[3] = ResourceServer::LoadGraph("res/suuji3.png");
	_cgSteps[4] = ResourceServer::LoadGraph("res/suuji4.png");
	_cgSteps[5] = ResourceServer::LoadGraph("res/suuji5.png");
	_cgSteps[6] = ResourceServer::LoadGraph("res/suuji6.png");
	_cgSteps[7] = ResourceServer::LoadGraph("res/suuji7.png");
	_cgSteps[8] = ResourceServer::LoadGraph("res/suuji8.png");
	_cgSteps[9] = ResourceServer::LoadGraph("res/suuji9.png");

	PlayMusic("res/sound/BGM07.mp3", DX_PLAYTYPE_LOOP);

	g._objServer.Add(new Player(g));
	g._objServer.Add(new Enemy(g));  //キュウリ君
	g._objServer.Add(new EnemyA(g));
	g._objServer.Add(new EnemyB(g));
	g._objServer.Add(new EnemyC(g));
	switch (g._gStageNo) {
	case GAME::STAGENO::ST2_1:
	case GAME::STAGENO::ST2_2:
	case GAME::STAGENO::ST2_3:
		g._objServer.Add(new EnemyD(g)); break;
	}
	g._objServer.Add(new Camera());
	g._objServer.Add(new Goal(g));

	// オブジェクト処理を行う
	_stopObjProcess = false;

	return true;
}

/**
 * 解放
 */
bool ModeGame::Terminate(Game& g){
	base::Terminate(g);

	g._objServer.Clear();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGame::Process(Game& g) {
	base::Process(g);
	if (_stopObjProcess == false){
		g._objServer.Process(g);
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeGame::Draw(Game& g){
	base::Draw(g);

	_bg.Draw(g); 
	g._mapChips->Draw(g);
	g._objServer.Draw(g); 

	for (int i = 0; i < 3; i++) {
		DrawGraph(CG_POS_X[i], CG_POS_Y[i], _cg[i], true);
	}
	if (_steps >= 0) {
		DrawGraph(CG_POS_X[3], CG_POS_Y[3], _cgSteps[_steps / 10], true);
		DrawGraph(CG_POS_X[4], CG_POS_Y[4], _cgSteps[_steps % 10], true);
	}

	return true;
}
