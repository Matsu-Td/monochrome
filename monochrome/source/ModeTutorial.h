/** 
 * @file   ModeTutorial.h
 * @brief  チュートリアルモードクラス
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief チュートリアルモードクラス
 */
class ModeTutorial : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

	int _cgNum;

private:
	static constexpr int  CG_X = 410, CG_Y = 215;  // 説明画面表示座標

	int _cg[10];  // 説明画面
};
