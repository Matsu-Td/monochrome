/** 
 * @file   ObjectBase.cpp
 * @brief  オブジェクト基底クラス
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "ObjectBase.h"
#include "game.h"
#include "math.h"

ObjectBase::ObjectBase()
{
	Init();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Init()
{
	_cut = 0;
	_cgNum = 1;
}

void ObjectBase::Process(Game& g)
{
	_cut++;
}

void ObjectBase::Draw(Game& g)
{
}

/**
 * 当たり判定
 */
bool ObjectBase::IsHit(ObjectBase& o)
{
	int w, h, length;
	w = o._nowx - _nowx;
	h = o._nowz - _nowz;
	length = static_cast<int>(sqrt(w * w + h * h));
	if (length < o._r + _r){
		return true;
	}
	return false;
}