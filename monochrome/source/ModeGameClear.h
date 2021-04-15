/** 
 * @file   ModeGameClear.h
 * @brief  ゲームクリアモードクラス
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"

/**
 * @brief ゲームクリアモードクラス
 */
class ModeGameClear : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

private:
	int	_cgGameClear;  // ゲームクリア画像
};