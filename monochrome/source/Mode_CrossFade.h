
/**
 * @file Mode_CrossFade.h
 * @brief �N���X�t�B�[�h����
 *
 * @date 2020-09-24
 * @author �������F
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
	 *  ��ʂ��L���v�`���A�t�F�[�h�J�E���g�w��
	 *  @param fadecnt �J�E���g��
	 */
	void Capture(int fadecnt);

protected:
	int	_cg;     // �t�F�[�h�p�S�̍���ʕ\��
	int	_cnt;    // �t�F�[�h�J�E���g
	int	_all;    // �t�F�[�h���J�E���g��
};