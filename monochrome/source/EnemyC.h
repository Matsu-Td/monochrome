/** 
 * @file   EnemyC.h
 * @brief  �G�l�~�[(�t���C�p��C)�N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "EnemyBase.h"

/**
 * @brief �G�l�~�[(�t���C�p��C)�N���X
 */
class EnemyC : public EnemyBase 
{
public:
	EnemyC(Game& g);
	~EnemyC();

	void Init(Game& g);
	void Process(Game& g);
};