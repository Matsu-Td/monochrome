/** 
 * @file   KyuriStageSelect.cpp
 * @brief  �X�e�[�W�I����ʂ̓G(�L���E���N)�\��
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "KyuriStageSelect.h"
#include "ResourceServer.h"
#include "ModeStageSelect.h"

KyuriStageSelect::KyuriStageSelect()
{
	_cg = ResourceServer::LoadGraph("res/kyuritatie.png");
	Init();
}

void KyuriStageSelect::Init()
{
	_x = 1400;
	_y = -95;
	_w = 220;
	_h = 95;
	_g = 0;
	_rotCnt = 0;
	_cntAll = 60;
}

/**
 * ��]�ړ����o����
 */
void KyuriStageSelect::Rotation()
{
	++_rotCnt;
	_x = POS_X - DIF_X * _rotCnt / _cntAll;
	_y = POS_Y - DIF_Y * _rotCnt / _cntAll;
	_angle += 1.0f;
	if (_rotCnt >= _cntAll) {
		_rotCnt = _cntAll;
	}
}

void KyuriStageSelect::Process(Game& g)
{
	// ��������
	if (_y < GROUND_Y) {
		++_g;
		_y += _g;
		if (_y >= GROUND_Y) {
			_y = GROUND_Y;
		}
	}
}

void KyuriStageSelect::Draw(Game& g)
{
	DrawRotaGraph2(_x, _y, _w / 2, _h / 2, 1.0f, _angle / 5.0f, _cg, TRUE, FALSE);
}