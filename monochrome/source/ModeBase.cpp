
/**
 * @file ModeBase.cpp
 * @brief ���[�h�x�[�X
 *
 * @date 2020-09-24
 * @author �������F
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

// ���Ԍo�߂�������
void ModeBase::StepTime(unsigned long tmNow) {
	// ���Ԍo�ߏ���
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

// �J�E���g��i�߂�
void ModeBase::StepCount() {
	_cntMode++;
}