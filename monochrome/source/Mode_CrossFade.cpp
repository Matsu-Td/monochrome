
/**
 * @file Mode_CrossFade.cpp
 * @brief �N���X�t�B�[�h����
 *
 * @date 2020-09-24
 * @author �������F
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
 * ��ʂ��L���v�`���A�t�F�[�h�J�E���g�w��
 */
void Mode_Overlay_CrossFade::Capture(int fadecnt)
{
	_cnt = fadecnt;
	_all = fadecnt;

	// ��ʃT�C�Y�Ɠ����X�N���[���̍쐬
	_cg = MakeGraph(SCREEN_W, SCREEN_H);

	// ��ʂɕ\������Ă���摜�̎�荞��
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

	// ���l���v�Z
	int alpha = 255 * _cnt / _all;

	// ��ɉ�ʂ�킹��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, _cg, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return true;
}