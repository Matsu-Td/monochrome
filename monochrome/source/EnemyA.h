#pragma once

/**
* @file EnemyA.h
* @brief �GA(�t���C�p��)�̈ړ�����
*
* @date 2020-09-24
* @author �������F
*/

#include "EnemyBase.h"

class EnemyA : public EnemyBase
{
public:
	EnemyA(Game& g);
	~EnemyA();

	void Init(Game& g);
	void Process(Game& g);

	static int _enemyAPosX;
	static int _enemyAPosZ;
};