/** 
 * @file   EnemyD.h
 * @brief  �G�l�~�[(�t���C�p��D)�N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "EnemyBase.h"

/**
 * @brief �G�l�~�[(�t���C�p��D)�N���X
 */
class EnemyD : public EnemyBase
{
public:
	EnemyD(Game& g);
	~EnemyD();

	void Init(Game& g);
	void Process(Game& g);
};