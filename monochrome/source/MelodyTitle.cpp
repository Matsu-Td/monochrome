
/**
 * @file MelodyTitle.cpp
 * @brief タイトル画面獲得音符表示
 *
 * @date 2020-09-20
 * @author 松尾忠彦
 */

#include "DxLib.h"
#include "MelodyTitle.h"
#include "ModeTitle.h"
#include "ResourceServer.h"

MelodyTitle::MelodyTitle()
{
	_cgMelody[0] = ResourceServer::LoadGraph("res/sibuonpu.png");
	_cgMelody[1] = ResourceServer::LoadGraph("res/hatibuonpu.png");
	_cgGosenhu = ResourceServer::LoadGraph("res/gosenhu.png");

	Init();
}

void MelodyTitle::Init()
{
	_w[0] = 45;
	_w[1] = 70;
	_h = 100;
	_melodyAlpha = 0.0f;
	_alphaSwitch = 0;
}

void MelodyTitle::Process(Game& g)
{
	float alphaSpd = 0.5f;
	//五線譜上に獲得したメロディのかけらを表示
	switch (_alphaSwitch) {
	case 0:
		_melodyAlpha += alphaSpd;
		if (_melodyAlpha >= ALPHA_MAX) {
			_alphaSwitch = 1;
		}break;
	case 1:
		_melodyAlpha -= alphaSpd;
		if (_melodyAlpha <= ALPHA_MIN) {
			_alphaSwitch = 0;
		}break;
	}
}

void MelodyTitle::Draw(Game& g)
{
	DrawGraph(0, 0, _cgGosenhu, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_melodyAlpha));
	for (int i = 0; i < MELODY_ALL; i++) {
		if (g._gMelodyTotal >= i + 1) { DrawRotaGraph2(X[i], Y[i], _w[i % 2] / 2, _h / 2, 0.8f, ROT[i] * DX_PI_F / 180.0f, _cgMelody[i % 2], TRUE, FALSE); }
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}