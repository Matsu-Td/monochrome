#pragma once

/**
 * @file EnemyB.h
 * @brief �GB(�t���C�p��)�̈ړ�����
 *
 * @date 2020-09-24
 * @author �������F
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