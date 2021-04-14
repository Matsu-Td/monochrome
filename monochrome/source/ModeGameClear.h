
/**
 * @file ModeGameClear.h
 * @brief �Q�[���N���A
 *
 * @date 2020-09-20
 * @author �������F
 */

#include "ModeBase.h"

class ModeGameClear : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

private:
	int	_cgGameClear;  // �Q�[���N���A�摜
};