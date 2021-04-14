/**
 * @file   ModeAmgLogo.h
 * @brief  AMGロゴ描画処理
 * 
 * @author matsuo tadahiko
 * @date   2020/09/20
 */

#include "ModeBase.h"

class ModeAmgLogo : public ModeBase{
	using base = ModeBase;

public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:
	static constexpr int ALPHA_MAX = 255;      // α最大値
	static constexpr int CG_AMGLOGO_X = 440, CG_AMGLOGO_Y = 440;   // ロゴ座標

	int _bg;        // 背景
	int _cg[2];     // ロゴ画像、フェード用全体黒画面表示
	int	_fadeCnt;   // フェード用カウント
	int	_fadeAll;   // フェード用総カウント数
	int _stayCnt;   // ロゴを表示するカウント
};