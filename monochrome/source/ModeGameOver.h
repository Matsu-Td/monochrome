
/**
 * @file ModeGameOver.h
 * @brief ゲームオーバー
 *
 * @date 2020-09-20
 * @author 松尾忠彦
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
	int	_cgGameOver;	// ゲームオーバー画像
};