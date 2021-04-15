/** 
 * @file   Mode_CrossFade.h
 * @brief  クロスフィードモードクラス
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief クロスフィードモードクラス
 */
class Mode_Overlay_CrossFade : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

	/*
	 *  画面をキャプチャ、フェードカウント指定
	 *  @param fadecnt カウント数
	 */
	void Capture(int fadecnt);

private:
	int	_cg;     // フェード用全体黒画面表示
	int	_cnt;    // フェードカウント
	int	_all;    // フェード総カウント数
};