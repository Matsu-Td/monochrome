#pragma once

/**
 * @file EnemyC.h
 * @brief �GC(�t���C�p��)�̈ړ�����
 *
 * @date 2020-09-24
 * @author �������F
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