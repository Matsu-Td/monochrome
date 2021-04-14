/**
 * @file   ModeAmgLogo.h
 * @brief  AMG���S�`�揈��
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
	static constexpr int ALPHA_MAX = 255;      // ���ő�l
	static constexpr int CG_AMGLOGO_X = 440, CG_AMGLOGO_Y = 440;   // ���S���W

	int _bg;        // �w�i
	int _cg[2];     // ���S�摜�A�t�F�[�h�p�S�̍���ʕ\��
	int	_fadeCnt;   // �t�F�[�h�p�J�E���g
	int	_fadeAll;   // �t�F�[�h�p���J�E���g��
	int _stayCnt;   // ���S��\������J�E���g
};