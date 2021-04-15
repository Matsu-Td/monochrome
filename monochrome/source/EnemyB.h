/** 
 * @file   EnemyB.h
 * @brief  エネミー(フライパンB)クラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "EnemyBase.h"

/**
 * @brief エネミー(フライパンB)クラス
 */
class EnemyB : public EnemyBase {
public:
	EnemyB(Game& g);
	~EnemyB();

	void Init(Game& g);
	void Process(Game& g);
};