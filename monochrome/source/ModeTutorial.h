
/**
 * @file ModeTutorial.h
 * @brief チュートリアル
 *
 * @date 2020-09-24
 * @author 松尾忠彦
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
	static constexpr int  CG_X = 410, CG_Y = 215;  // 説明画面表示座標

	int _cg[10];  // 説明画面
};
