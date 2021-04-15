/** 
 * @file   ModeGameClear.h
 * @brief  �Q�[���N���A���[�h�N���X
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief �Q�[���N���A���[�h�N���X
 */
class ModeGameClear : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

private:
	int	_cgGameClear;  // �Q�[���N���A�摜
};