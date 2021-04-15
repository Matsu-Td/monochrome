/** 
 * @file   EnemyC.h
 * @brief  エネミー(フライパンC)クラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "EnemyBase.h"

/**
 * @brief エネミー(フライパンC)クラス
 */
class EnemyC : public EnemyBase 
{
public:
	EnemyC(Game& g);
	~EnemyC();

	void Init(Game& g);
	void Process(Game& g);
};