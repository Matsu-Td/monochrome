#pragma once

/**
 * @file EnemyD.h
 * @brief �GD(�t���C�p��)�̈ړ�����
 *
 * @date 2020-09-24
 * @author �������F
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