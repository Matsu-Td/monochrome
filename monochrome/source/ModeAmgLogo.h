/** 
 * @file   ModeAmgLogo.h
 * @brief  AMGロゴ表示
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief AMGロゴモードクラス
 */
class ModeAmgLogo : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

protected:
	static constexpr int ALPHA_MAX = 255;      // α最大値
	static constexpr int CG_AMGLOGO_X = 440, CG_AMGLOGO_Y = 440;   // ロゴ座標

	int _bg;        // 背景
	int _cg[2];     // ロゴ画像、フェード用全体黒画面表示
	int	_fadeCnt;   // フェード用カウント
	int	_fadeAll;   // フェード用総カウント数
	int _stayCnt;   // ロゴを表示するカウント
};