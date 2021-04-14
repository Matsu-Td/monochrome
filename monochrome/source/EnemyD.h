#pragma once

/**
 * @file EnemyD.h
 * @brief GD(tCp)ÌÚ®
 *
 * @date 2020-09-24
 * @author ¼öF
 */

#include "EnemyBase.h"

class EnemyD : public EnemyBase
{
public:
	EnemyD(Game& g);
	~EnemyD();

	void Init(Game& g);
	void Process(Game& g);
};