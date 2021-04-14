/**
 * @file   ModeGameOver.h
 * @brief  ゲームオーバーモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/09/20
 */

#include "ModeBase.h"

class ModeGameOver : public ModeBase{
	using base = ModeBase;

public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:
	int	_cgGameOver;	// ゲームオーバー画像
};