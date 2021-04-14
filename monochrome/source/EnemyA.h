#pragma once

/**
* @file EnemyA.h
* @brief “GA(ƒtƒ‰ƒCƒpƒ“)‚ÌˆÚ“®ˆ—
*
* @date 2020-09-24
* @author ¼”ö’‰•F
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