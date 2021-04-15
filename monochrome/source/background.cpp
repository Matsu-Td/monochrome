/** 
 * @file   background.cpp
 * @brief  �w�i�N���X
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "background.h"
#include "ResourceServer.h"
#include "Game.h"

BackGround::BackGround()
{
	_cg = ResourceServer::LoadGraph("res/haikeihaiiro.png");     //�w�i�摜�����[�h����
}

BackGround::~BackGround()
{
}

void BackGround::Draw(Game& g)
{              
	DrawGraph(0, 0, _cg, false);      
}
