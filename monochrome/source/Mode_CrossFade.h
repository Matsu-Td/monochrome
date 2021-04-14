
/**
 * @file Mode_CrossFade.h
 * @brief クロスフィード処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */


#include "ModeBase.h"

class Mode_Overlay_CrossFade : public ModeBase
{
	using base = ModeBase;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	/*
	 *  画面をキャプチャ、フェードカウント指定
	 *  @param fadecnt カウント数
	 */
	void Capture(int fadecnt);

protected:
	int	_cg;     // フェード用全体黒画面表示
	int	_cnt;    // フェードカウント
	int	_all;    // フェード総カウント数
};