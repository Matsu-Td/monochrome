/**
 * @file   ModeGameClear.h
 * @brief  ゲームクリアモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/09/20
 */

#include "ModeBase.h"

class ModeGameClear : public ModeBase{
	using base = ModeBase;

public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

private:
	int	_cgGameClear;  // ゲームクリア画像
};