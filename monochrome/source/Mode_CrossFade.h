/** 
 * @file   Mode_CrossFade.h
 * @brief  �N���X�t�B�[�h���[�h�N���X
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief �N���X�t�B�[�h���[�h�N���X
 */
class Mode_Overlay_CrossFade : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

	/*
	 *  ��ʂ��L���v�`���A�t�F�[�h�J�E���g�w��
	 *  @param fadecnt �J�E���g��
	 */
	void Capture(int fadecnt);

private:
	int	_cg;     // �t�F�[�h�p�S�̍���ʕ\��
	int	_cnt;    // �t�F�[�h�J�E���g
	int	_all;    // �t�F�[�h���J�E���g��
};