#pragma once

/**
 * @file background.h
 * @brief �w�i�`��
 *
 * @date 2020-09-24
 * @author �������F
 */

#include "ObjectBase.h"

class BackGround
{
public:
	BackGround();
	~BackGround();

	void Draw(Game& g);

private:
	int _cg;       //�w�i�摜
};