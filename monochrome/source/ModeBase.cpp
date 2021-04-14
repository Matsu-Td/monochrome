
/**
 * @file ModeBase.cpp
 * @brief モードベース
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "DxLib.h"
#include "ModeBase.h"

ModeBase::ModeBase() {
	_szName = "";
	_uid = 1;
	_layer = 0;

	_cntMode = 0;
	_tmMode = 0;
	_tmStep = 0;
	_tmModeBase = 0;
	_tmPauseBase = 0;
	_tmPauseStep = 0;
	_tmOldFrame = 0;

	SetCallPerFrame(1);
	SetCallOfCount(1);
}

ModeBase::~ModeBase() {
}

bool	ModeBase::Initialize(Game& g) {

	return true;
}

bool	ModeBase::Terminate(Game& g) {

	return true;
}

bool	ModeBase::Process(Game& g)
{
	return	true;
}


bool	ModeBase::Draw(Game& g)
{
	return	true;
}

// 時間経過をさせる
void ModeBase::StepTime(unsigned long tmNow) {
	// 時間経過処理
	if (_cntMode == 0) {
		_tmMode = 0;
		_tmStep = 0;
		_tmModeBase = tmNow;
		_tmPauseBase = 0;
		_tmPauseStep = 0;
	}
	else {
		_tmMode = tmNow - _tmModeBase + _tmPauseStep;
		_tmStep = tmNow - _tmOldFrame;
	}
	_tmOldFrame = tmNow;
}

// カウントを進める
void ModeBase::StepCount() {
	_cntMode++;
}