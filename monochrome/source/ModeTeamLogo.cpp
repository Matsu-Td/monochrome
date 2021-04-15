/** 
 * @file   ModeTeamLogo.cpp
 * @brief  �`�[�����S�\��
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"
#include "Mode_CrossFade.h"
#include "ModeTitle.h"
#include "ModeTeamLogo.h"

bool ModeTeamLogo::Initialize(Game& g) {
	if (!base::Initialize(g)) { return false; }

	_bg = ResourceServer::LoadGraph("res/haikeihaiiro.png");
	_cg[0] = ResourceServer::LoadGraph("res/teamrogo.png");

	// ��ʃT�C�Y�Ɠ����X�N���[���̍쐬
	_cg[1] = MakeGraph(SCREEN_W, SCREEN_H);

	// ��ʂɕ\������Ă���摜�̎�荞��
	GetDrawScreenGraph(0, 0, SCREEN_W, SCREEN_H, _cg[1]);

	_mode = 0;
	_fadeAll = 30;
	_fadeCnt = _fadeAll;
	_stayCnt = 120;

	return true;
}

bool ModeTeamLogo::Terminate(Game& g) {
	base::Terminate(g);

	DeleteGraph(_cg[0]);

	return true;
}

bool ModeTeamLogo::Process(Game& g) {
	base::Process(g);

	if (_mode == 0) { _fadeCnt--; }
	if (_fadeCnt <= 0) {
		_fadeCnt = 0;
		_mode = 1;
	}
	if (_mode == 1) {
		_stayCnt--;
		if (_stayCnt <= 0) {
			_mode = 2;
		}
	}
	if (_mode == 2) {
		_fadeCnt++;
		if (_fadeCnt >= _fadeAll) {
			g._serverMode->Del(this);

			ModeTitle* modeTitle = new ModeTitle();
			g._serverMode->Add(modeTitle, 0, "Title");
		}
	}

	return true;
}

bool ModeTeamLogo::Draw(Game& g) {
	base::Draw(g);

	// ���l���v�Z
	int alpha = ALPHA_MAX * _fadeCnt / _fadeAll;

	DrawGraph(0, 0, _bg, FALSE);
	DrawGraph(CG_TEAMLOGO_X, CG_TEAMLOGO_Y, _cg[0], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, _cg[1], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return true;
}