#pragma once

/**
 * @file game.h
 * @brief ゲーム本体
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "ModeServer.h"
#include "ObjectServer.h"
#include "background.h"
#include "player.h"
#include "Enemy.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "EnemyC.h"
#include "EnemyD.h"
#include "Goal.h"
#include "Camera.h"
#include "mapchips.h"
#include "Note.h"
#include <unordered_map>

// 画面設定
constexpr auto SCREEN_W = 1920;    // 画面の横解像度
constexpr auto SCREEN_H = 1080;    // 画面の縦解像度
constexpr auto SCREEN_DEPTH = 32;  // 1ドット当たりのビット数

namespace GAME {
	enum STAGENO {
		TUTORIAL,  // チュートリアル
		ST1_1,     // ステージ1-1
		ST1_2,     // ステージ1-2
		ST1_3,     // ステージ1-3
		ST2_1,     // ステージ2-1
		ST2_2,     // ステージ2-2
		ST2_3,     // ステージ2-3
	};
}

namespace CHARA {
	enum STATE{  // 移動、向きの状態
		FALL,          // 落下
		STOP,          // 停止
		RIGHT_DOWN,    // 右下移動
		LEFT_UP,       // 左上移動
		RIGHT_UP,      // 右上移動
		LEFT_DOWN,     // 左下移動
	};
}

class Game {
public:
	Game();             // アプリの初期化
	~Game();            // アプリの解放

	void Input();       // フレーム処理数：入力
	void Process();     // フレーム処理数：計算
	void Draw();        // フレーム処理数：描画

	// ゲーム情報
	int _gkey;                    // キー入力の情報
	int _gTrg;                    // キー入力のトリガ情報
	int _gFrameCount;             // マイフレーム+1するカウント
	int _gStageNo;                // ステージ番号
	int _gMelodyTotal;            // メロディのかけらの入手数、合計
	bool _gHasKyuri;              // キュウリ君(音符)獲得フラグ(false：未、true：済)
	bool _gHasLanding;			  // 移動スタートフラグ(false：ナス君着地待ち、true：移動開始)
	bool _gHasGameEnd;            // ゲーム終了フラグ(true：ゲーム終了)
	
	ModeServer *_serverMode;    
	ObjectServer _objServer;    
	MapChips* _mapChips;     
	
	std::unordered_map<std::string, int> _se;

	// キャラマップ(JSONマップデータを変換する)
	int _gCharaMap[14][11]{ 
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0
	};
};