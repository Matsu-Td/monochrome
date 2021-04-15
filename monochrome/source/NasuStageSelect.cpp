/** 
 * @file   NasuStageSelect.cpp
 * @brief  ステージ選択画面でのプレイヤー(ナス君)移動処理
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "ResourceServer.h"
#include "NasuStageSelect.h"
#include "ModeStageSelect.h"

NasuStageSelect::NasuStageSelect()
{
	_cg[0] = ResourceServer::LoadGraph("res/nasutachie.png");
	_cg[1] = ResourceServer::LoadGraph("res/nasuidou_1.png");
	_cg[2] = ResourceServer::LoadGraph("res/nasuidou_2.png");
	_cg[3] = ResourceServer::LoadGraph("res/nasuidou_3.png");

	Init();
}

void NasuStageSelect::Init()
{
	_direction = PLAYER_RIGHT;
	_x = 735;
	_y = -188;
	_w = 157;
	_h = 125;
	_oldX = 0;
	_oldY = 0;
	_g = 0;
	_all = 30;
	_moveTime = 0;
	_state = CHARA::STATE::STOP;
	_angle = 0.0f;
	_rotCnt = 0;
	_subX = 0;
	_subY = 0;
}

/**
 * ナス君状態,ステージ切替処理
 */
void NasuStageSelect::MoveStage(Game& g, int state, int direction, int nextStage)
{
	_state = state;
	_direction = direction;
	g._gStageNo += nextStage;
	PlaySoundMem(g._se["slide1"], DX_PLAYTYPE_BACK);
	StageSlide::_slideState = true;
}

/**
 * ナス君移動、モーション処理
 */
void NasuStageSelect::MoveMotion(int moveX, int moveY)
{
	++_moveTime;
	_x = _oldX + (BLOCK_MOVE_X * moveX) * _moveTime / _all;
	_y = _oldY + (BLOCK_MOVE_Y * moveY) * _moveTime / _all;
	if (_moveTime == _all) {
		_state = CHARA::STATE::STOP;
		_moveTime = 0;
		_oldX = _x; _oldY = _y;
	}
}

/**
 * 回転移動座標 差分処理
 */
void NasuStageSelect::SubPosition()
{
	_subX = _x - MOVE_POS_X;
	_subY = _y - MOVE_POS_Y;
	_rotX = _x;
	_rotY = _y;
}

/**
 * 回転移動演出処理
 */
void NasuStageSelect::Rotation()
{
	++_rotCnt;
	_x = _rotX - (_subX * _rotCnt / ROT_CNT_ALL);
	_y = _rotY - (_subY * _rotCnt / ROT_CNT_ALL);
	_angle += 1.0f;
	if (_rotCnt >= ROT_CNT_ALL) {
		_rotCnt = ROT_CNT_ALL;
	}
}

void NasuStageSelect::Process(Game& g)
{
	if (_state == CHARA::STATE::STOP) {
		if (g._gTrg & PAD_INPUT_LEFT && g._gStageNo > 1 && 
			StageSlide::_oldStageNo == g._gStageNo && 
			StageSlide::_slideState == false) {
			if (_x == 808 && _y == 895 || _x == 954 && _y == 895 || _x == 1100 && _y == 895) {
				MoveStage(g, CHARA::STATE::LEFT_UP, PLAYER_LEFT, -1);
			}
			else if (_x == 881 && _y == 853 || _x == 1027 && _y == 853) {
				MoveStage(g, CHARA::STATE::LEFT_DOWN, PLAYER_LEFT, -1);
			}
		}

		if (g._gTrg & PAD_INPUT_RIGHT && g._gStageNo < 6 && 
			StageSlide::_oldStageNo == g._gStageNo && 
			StageSlide::_slideState == false) {
			if (_x == 735 && _y == 853) {
				if (g._gMelodyTotal >= 1) {
				     MoveStage(g, CHARA::STATE::RIGHT_DOWN, PLAYER_RIGHT, 1);
				}
				else { PlaySoundMem(g._se["slide2"], DX_PLAYTYPE_BACK); }
			}
			else if (_x == 808 && _y == 895) {
				if (g._gMelodyTotal >= 2) {
				    MoveStage(g, CHARA::STATE::RIGHT_UP, PLAYER_RIGHT, 1);
				}
				else { PlaySoundMem(g._se["slide2"], DX_PLAYTYPE_BACK); }
			}
			else if (_x == 881 && _y == 853) {
				if (g._gMelodyTotal >= 3) {
					MoveStage(g, CHARA::STATE::RIGHT_DOWN, PLAYER_RIGHT, 1);
				}
				else { PlaySoundMem(g._se["slide2"], DX_PLAYTYPE_BACK); }
			}
			else if (_x == 954 && _y == 895) {
				if (g._gMelodyTotal >= 4) {
					MoveStage(g, CHARA::STATE::RIGHT_UP, PLAYER_RIGHT, 1);
				}
				else { PlaySoundMem(g._se["slide2"], DX_PLAYTYPE_BACK); }
			}
			else if (_x == 1027 && _y == 853) {
				if (g._gMelodyTotal >= 5) {
					MoveStage(g, CHARA::STATE::RIGHT_DOWN, PLAYER_RIGHT, 1);
				}
				else { PlaySoundMem(g._se["slide2"], DX_PLAYTYPE_BACK); }
			}
		}
	}
	switch (_state) {
	case CHARA::STATE::LEFT_UP:
		MoveMotion(-1, -1); break;
	case CHARA::STATE::RIGHT_DOWN:
		MoveMotion(1, 1); break;
	case CHARA::STATE::RIGHT_UP:
		MoveMotion(1, -1); break;
	case CHARA::STATE::LEFT_DOWN:
		MoveMotion(-1, 1); break;
	default:
		_oldX = _x; _oldY = _y; break;
	}

	// 落下処理
	if (_y < GROUND_Y) {
		++_g;
		_y += _g;
		if (_y >= GROUND_Y) {
			_y = GROUND_Y;
		}
	}
}

void NasuStageSelect::Draw(Game& g)
{
	if (_direction == PLAYER_RIGHT) { DrawRotaGraph2(_x, _y, _w / 2, _h / 2, 1.0f, _angle / 5.0f, _cg[(_moveTime + 8) / 10], TRUE, FALSE); }
	if (_direction == PLAYER_LEFT) { DrawRotaGraph2(_x, _y, _w / 2, _w / 2, 1.0f, _angle / 5.0f, _cg[(_moveTime + 8) / 10], TRUE, TRUE); }
}