
/**
 * @file Mode_CrossFade.cpp
 * @brief クロスフィード処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "DxLib.h"
#include "Mode_CrossFade.h"
#include "Game.h"
#include "ResourceServer.h"

bool Mode_Overlay_CrossFade::Initialize(Game& g) 
{
	if (!base::Initialize(g)) { return false; }
	return true;
}

bool Mode_Overlay_CrossFade::Terminate(Game& g)
{
	base::Terminate(g);

	DeleteGraph(_cg);

	return true;
}

/**
 * 画面をキャプチャ、フェードカウント指定
 */
void Mode_Overlay_CrossFade::Capture(int fadecnt)
{
	_cnt = fadecnt;
	_all = fadecnt;

	// 画面サイズと同じスクリーンの作成
	_cg = MakeGraph(SCREEN_W, SCREEN_H);

	// 画面に表示されている画像の取り込み
	GetDrawScreenGraph(0, 0, SCREEN_W, SCREEN_H, _cg);
}

bool Mode_Overlay_CrossFade::Process(Game& g)
{
	base::Process(g);

	_cnt--;
	if (_cnt <= 0) {
		g._serverMode->Del(this);
	}

	return true;
}

bool Mode_Overlay_CrossFade::Draw(Game& g) 
{
	base::Draw(g);

	// α値を計算
	int alpha = 255 * _cnt / _all;

	// 上に画面を被せる
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, _cg, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return true;
}