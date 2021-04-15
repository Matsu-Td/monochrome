/** 
 * @file   EnemyD.h
 * @brief  エネミー(フライパンD)クラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "EnemyBase.h"

/**
 * @brief エネミー(フライパンD)クラス
 */
class EnemyD : public EnemyBase
{
public:
	EnemyD(Game& g);
	~EnemyD();

	void Init(Game& g);
	void Process(Game& g);
};