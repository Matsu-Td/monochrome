
/**
 * @file ModeGame.h
 * @brief ゲームモード
 *
 * @date 2020-09-20
 * @author 松尾忠彦
 */

#include "ModeBase.h"
#include "ObjectServer.h"
#include "background.h"
#include "player.h"
#include "Enemy.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "EnemyC.h"
#include "EnemyD.h"
#include "Goal.h"
#include "Note.h"
#include "Camera.h"

class ModeGame : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	bool _stopObjProcess;       // オブジェクト処理をストップ
	static int _steps;          // 歩数

private:
	static constexpr int STEPS_TUTORIAL = 40;  // 総歩数：チュートリアル
	static constexpr int STEPS1_1 = 40;        // 総歩数：ステージ1-1
	static constexpr int STEPS1_2 = 30;        // 総歩数：ステージ1-2
	static constexpr int STEPS1_3 = 45;        // 総歩数：ステージ1-3
	static constexpr int STEPS2_1 = 35;        // 総歩数：ステージ2-1
	static constexpr int STEPS2_2 = 30;        // 総歩数：ステージ2-2
	static constexpr int STEPS2_3 = 35;        // 総歩数：ステージ2-3

	// 画像描画座標  =  {のこり, AHS簡易表示, 操作ガイド, 歩数10の位, 歩数1の位 }
	const int CG_POS_X[5] = { 1500,120,1560,1660,1720 };
	const int CG_POS_Y[5] = { 920,360,50,920,920 };

protected:
	BackGround _bg;       // 背景

	int _cg[3];           // 画像
	int _cgSteps[10];     // 歩数表示用の画像
};