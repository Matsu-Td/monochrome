/** 
 * @file   background.h
 * @brief  �w�i�N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "ObjectBase.h"

/**
 * @brief �w�i�N���X
 */
class BackGround
{
public:
	BackGround();
	~BackGround();

	void Draw(Game& g);

private:
	int _cg;       //�w�i�摜
};