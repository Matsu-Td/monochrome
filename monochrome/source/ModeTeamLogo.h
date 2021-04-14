
/**
 * @file ModeTeamLogo.h
 * @brief �`�[�����S�\��
 *
 * @date 2020-09-20
 * @author �������F
 */

#include "ModeBase.h"

class ModeTeamLogo : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:
	static constexpr int ALPHA_MAX = 255;   // ���ő�l
	static constexpr int CG_TEAMLOGO_X = 600, CG_TEAMLOGO_Y = 440;  // ���S���W

	int _bg;       // �w�i
	int _cg[2];    // ���S�摜�A�t�F�[�h�p�S�̍���ʕ\��
	int	_fadeCnt;  // �t�F�[�h�p�J�E���g
	int	_fadeAll;  // �t�F�[�h�p���J�E���g��
	int _stayCnt;  // ���S��\������J�E���g
};
