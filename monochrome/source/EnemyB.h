#pragma once

/**
 * @file EnemyB.h
 * @brief “GB(ƒtƒ‰ƒCƒpƒ“)‚ÌˆÚ“®ˆ—
 *
 * @date 2020-09-24
 * @author ¼”ö’‰•F
 */

#include "EnemyBase.h"

class EnemyB : public EnemyBase 
{
public:
	EnemyB(Game& g);
	~EnemyB();

	void Init(Game& g);
	void Process(Game& g);
};