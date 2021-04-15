/** 
 * @file   ModeGameOver.h
 * @brief  ゲームオーバークラス
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief ゲームオーバークラス
 */
class ModeGameOver : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

private:
	int	_cgGameOver;	// ゲームオーバー画像
};