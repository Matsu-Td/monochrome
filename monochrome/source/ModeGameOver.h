
/**
 * @file ModeGameOver.h
 * @brief �Q�[���I�[�o�[
 *
 * @date 2020-09-20
 * @author �������F
 */

#include "ModeBase.h"

class ModeGameOver : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:
	int	_cgGameOver;	// �Q�[���I�[�o�[�摜
};