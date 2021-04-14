#pragma once

/**
 * @file EnemyC.h
 * @brief “GC(ƒtƒ‰ƒCƒpƒ“)‚ÌˆÚ“®ˆ—
 *
 * @date 2020-09-24
 * @author ¼”ö’‰•F
 */

#include "EnemyBase.h"

class EnemyC : public EnemyBase 
{
public:
	EnemyC(Game& g);
	~EnemyC();

	void Init(Game& g);
	void Process(Game& g);
};