/** 
 * @file   EnemyA.h
 * @brief  �G�l�~�[(�t���C�p��A)�N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "EnemyBase.h"

class EnemyA : public EnemyBase{
public:
	EnemyA(Game& g);
	~EnemyA();

	void Init(Game& g);
	void Process(Game& g);

	static int _enemyAPosX;
	static int _enemyAPosZ;
};