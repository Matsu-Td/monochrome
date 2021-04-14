
/**
 * @file ModeTutorial.h
 * @brief �`���[�g���A��
 *
 * @date 2020-09-24
 * @author �������F
 */

#include "ModeBase.h"

class ModeTutorial : public ModeBase
{
	using base = ModeBase;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	int _cgNum;

protected:
	static constexpr int  CG_X = 410, CG_Y = 215;  // ������ʕ\�����W

	int _cg[10];  // �������
};
