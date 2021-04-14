
/**
 * @file ModeGameClear.h
 * @brief ゲームクリア
 *
 * @date 2020-09-20
 * @author 松尾忠彦
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
	int	_cgGameClear;  // ゲームクリア画像
};