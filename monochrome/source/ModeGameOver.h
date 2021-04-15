/** 
 * @file   ModeGameOver.h
 * @brief  �Q�[���I�[�o�[�N���X
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief �Q�[���I�[�o�[�N���X
 */
class ModeGameOver : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

private:
	int	_cgGameOver;	// �Q�[���I�[�o�[�摜
};