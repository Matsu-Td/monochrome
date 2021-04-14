
/**
 * @file background.cpp
 * @brief ”wŒi•`‰æ
 *
 * @date 2020-09-24
 * @author ¼”ö’‰•F
 */

#include "DxLib.h"
#include "background.h"
#include "ResourceServer.h"
#include "Game.h"

BackGround::BackGround()
{
	_cg = ResourceServer::LoadGraph("res/haikeihaiiro.png");     //”wŒi‰æ‘œ‚ğƒ[ƒh‚·‚é
}

BackGround::~BackGround()
{
}

void BackGround::Draw(Game& g)
{              
	DrawGraph(0, 0, _cg, false);      
}
