/** 
 * @file   ModeTutorial.h
 * @brief  �`���[�g���A�����[�h�N���X
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief �`���[�g���A�����[�h�N���X
 */
class ModeTutorial : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

	int _cgNum;

private:
	static constexpr int  CG_X = 410, CG_Y = 215;  // ������ʕ\�����W

	int _cg[10];  // �������
};
