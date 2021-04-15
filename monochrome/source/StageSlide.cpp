/** 
 * @file   StageSlide.cpp
 * @brief  ステージ選択、スライド処理
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "ResourceServer.h"
#include "StageSlide.h"

bool StageSlide::_slideState;
int StageSlide::_oldStageNo;

StageSlide::StageSlide()
{
	_cgStage[0] = ResourceServer::LoadGraph("res/stage1-1.png");
	_cgStage[1] = ResourceServer::LoadGraph("res/stage1-2.png");
	_cgStage[2] = ResourceServer::LoadGraph("res/stage1-3.png");
	_cgStage[3] = ResourceServer::LoadGraph("res/stage2-1.png");
	_cgStage[4] = ResourceServer::LoadGraph("res/stage2-2.png");
	_cgStage[5] = ResourceServer::LoadGraph("res/stage2-3.png");

	Init();
}

void StageSlide::Init()
{
	_slideCnt = 0;
	_slideAll = 30;
	_slideState = false;
	_oldStageNo = 1;
}

/**
 * ステージスライド画像 左位置 ⇒ 真ん中へ移動 & サイズUP
 */
void StageSlide::SlidePatternA(int slideNo)
{
	_x[slideNo] = _oldX[slideNo] + (PAT_AB_DELTA_X * _slideCnt / _slideAll);
	_y[slideNo] = _oldY[slideNo] - (DELTA_Y * _slideCnt / _slideAll);
	_w[slideNo] = _oldW[slideNo] + (DELTA_W * _slideCnt / _slideAll);
	_h[slideNo] = _oldH[slideNo] + (DELTA_H * _slideCnt / _slideAll);
}

/**
 * ステージスライド画像 真ん中 ⇒ 左位置へ移動 & サイズDOWN
 */
void StageSlide::SlidePatternB(int slideNo)
{
	_x[slideNo] = _oldX[slideNo] - (PAT_AB_DELTA_X * _slideCnt / _slideAll);
	_y[slideNo] = _oldY[slideNo] + (DELTA_Y * _slideCnt / _slideAll);
	_w[slideNo] = _oldW[slideNo] - (DELTA_W * _slideCnt / _slideAll);
	_h[slideNo] = _oldH[slideNo] - (DELTA_H * _slideCnt / _slideAll);
}

/**
 * ステージスライド画像 真ん中 ⇒ 右位置へ移動 & サイズDOWN
 */
void StageSlide::SlidePatternC(int slideNo)
{
	_x[slideNo] = _oldX[slideNo] + (PAT_CD_DELTA_X * _slideCnt / _slideAll);
	_y[slideNo] = _oldY[slideNo] + (DELTA_Y * _slideCnt / _slideAll);
	_w[slideNo] = _oldW[slideNo] - (DELTA_W * _slideCnt / _slideAll);
	_h[slideNo] = _oldH[slideNo] - (DELTA_H * _slideCnt / _slideAll);
}

/**
 * ステージスライド画像 右位置 ⇒ 真ん中へ移動 & サイズUP
 */
void StageSlide::SlidePatternD(int slideNo)
{
	_x[slideNo] = _oldX[slideNo] - (PAT_CD_DELTA_X * _slideCnt / _slideAll);
	_y[slideNo] = _oldY[slideNo] - (DELTA_Y * _slideCnt / _slideAll);
	_w[slideNo] = _oldW[slideNo] + (DELTA_W * _slideCnt / _slideAll);
	_h[slideNo] = _oldH[slideNo] + (DELTA_H * _slideCnt / _slideAll);
}

/**
 * ステージスライド画像 左もしくは右へ移動(サイズ変更なし)
 */
void StageSlide::SlidePatternE(int slideNo, int direction)
{
	_x[slideNo] = _oldX[slideNo] + ((PAT_E_DELTA_X * direction) * _slideCnt / _slideAll);
}

void StageSlide::Process(Game& g)
{
	// ステージスライド画像処理
	if (_slideState == true) {
		switch (g._gStageNo) {
		case GAME::STAGENO::ST1_1:
			_slideCnt++;
			SlidePatternA(0);
			SlidePatternC(1);
			SlidePatternE(2, 1);
			if (_slideCnt >= _slideAll) {
				_slideCnt = _slideAll;
				_slideState = false;
			}
			break;
		case GAME::STAGENO::ST1_2:
			_slideCnt++;
			if (_oldStageNo == GAME::STAGENO::ST1_1) {
				SlidePatternB(0);
				SlidePatternD(1);
				SlidePatternE(2, -1);
			}
			if (_oldStageNo == GAME::STAGENO::ST1_3) {
				SlidePatternE(0, 1);
				SlidePatternA(1);
				SlidePatternC(2);
				SlidePatternE(3, 1);
			}
			if (_slideCnt >= _slideAll) {
				_slideCnt = _slideAll;
				_slideState = false;
			}
			break;
		case GAME::STAGENO::ST1_3:
			_slideCnt++;
			if (_oldStageNo == GAME::STAGENO::ST1_2) {
				SlidePatternE(0, -1);
				SlidePatternB(1);
				SlidePatternD(2);
				SlidePatternE(3, -1);
			}
			if (_oldStageNo == GAME::STAGENO::ST2_1) {
				SlidePatternE(1, 1);
				SlidePatternA(2);
				SlidePatternC(3);
				SlidePatternE(4, 1);
			}
			if (_slideCnt >= _slideAll) {
				_slideCnt = _slideAll;
				_slideState = false;
			}
			break;
		case GAME::STAGENO::ST2_1:
			_slideCnt++;
			if (_oldStageNo == GAME::STAGENO::ST1_3) {
				SlidePatternE(1, -1);
				SlidePatternB(2);
				SlidePatternD(3);
				SlidePatternE(4, -1);
			}
			if (_oldStageNo == GAME::STAGENO::ST2_2) {
				SlidePatternE(2, 1);
				SlidePatternA(3);
				SlidePatternC(4);
				SlidePatternE(5, 1);
			}
			if (_slideCnt >= _slideAll) {
				_slideCnt = _slideAll;
				_slideState = false;
			}
			break;
		case GAME::STAGENO::ST2_2:
			_slideCnt++;
			if (_oldStageNo == GAME::STAGENO::ST2_1) {
				SlidePatternE(2, -1);
				SlidePatternB(3);
				SlidePatternD(4);
				SlidePatternE(5, -1);
			}
			if (_oldStageNo == GAME::STAGENO::ST2_3) {
				SlidePatternE(3, 1);
				SlidePatternA(4);
				SlidePatternC(5);
			}
			if (_slideCnt >= _slideAll) {
				_slideCnt = _slideAll;
				_slideState = false;
			}
			break;
		case GAME::STAGENO::ST2_3:
			_slideCnt++;
			if (_oldStageNo == GAME::STAGENO::ST2_2) { SlidePatternE(3, -1); }
			SlidePatternB(4);
			SlidePatternD(5);
			if (_slideCnt >= _slideAll) {
				_slideCnt = _slideAll;
				_slideState = false;
			}
			break;
		}
	}
	else {
		_slideCnt = 0;
		for (int i = 0; i < 6; i++) {
			_oldX[i] = _x[i];
			_oldY[i] = _y[i];
			_oldW[i] = _w[i];
			_oldH[i] = _h[i];
			_oldStageNo = g._gStageNo;
		}
	}
}

void StageSlide::Draw(Game& g)
{
	for (int i = 0; i < 6; i++) {        // ステージ画像
		if (i > g._gMelodyTotal) {
			SetDrawBright(50, 50, 50);   //	解放されていないステージ画像は暗く(輝度を下げて)表示する
		}
		DrawExtendGraph(_x[i], _y[i], _x[i] + _w[i], _y[i] + _h[i], _cgStage[i], TRUE);
		SetDrawBright(255, 255, 255);
	}
}