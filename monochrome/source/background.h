/** 
 * @file   background.h
 * @brief  ”wŒiƒNƒ‰ƒX
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "ObjectBase.h"

/**
 * @brief ”wŒiƒNƒ‰ƒX
 */
class BackGround
{
public:
	BackGround();
	~BackGround();

	void Draw(Game& g);

private:
	int _cg;       //”wŒi‰æ‘œ
};