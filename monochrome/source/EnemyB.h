/** 
 * @file   EnemyB.h
 * @brief  �G�l�~�[(�t���C�p��B)�N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "EnemyBase.h"

/**
 * @brief �G�l�~�[(�t���C�p��B)�N���X
 */
class EnemyB : public EnemyBase {
public:
	EnemyB(Game& g);
	~EnemyB();

	void Init(Game& g);
	void Process(Game& g);
};