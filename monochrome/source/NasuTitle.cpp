/** 
 * @file   NasuTitle.cpp
 * @brief  タイトル画面のプレイヤー移動処理
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "NasuTitle.h"
#include "ModeTitle.h"
#include "ResourceServer.h"

NasuTitle::NasuTitle()
{
	_cg[0] = ResourceServer::LoadGraph("res/nasutachie.png");
	_cg[1] = ResourceServer::LoadGraph("res/nasuidou_1.png");
	_cg[2] = ResourceServer::LoadGraph("res/nasuidou_2.png");
	_cg[3] = ResourceServer::LoadGraph("res/nasuidou_3.png");

	Init();
}

void NasuTitle::Init()
{
	_direction = PLAYER_RIGHT;
	_x = 518;
	_y = -125;
	_oldX = 0;
	_oldY = 0;
	_g = 0;
	_moveAll = 30;
	_moveTime = 0;
	_state = CHARA::STATE::FALL;
}

void NasuTitle::MoveMotion(int moveX, int moveY)
{
	++_moveTime;
	_x = _oldX + (BLOCK_MOVE_X * moveX) * _moveTime / _moveAll;
	_y = _oldY + (BLOCK_MOVE_Y * moveY) * _moveTime / _moveAll;
	if (_moveTime == _moveAll) {
		_state = CHARA::STATE::STOP;
		_moveTime = 0;
		_oldX = _x; _oldY = _y;
	}
}

void NasuTitle::Process(Game& g)
{
	if (_state == CHARA::STATE::STOP) {
		if (g._gkey & PAD_INPUT_UP) {
			if (_x == 591 && _y == 572 || _x == 664 && _y == 614 ||
				_x == 737 && _y == 656 || _x == 810 && _y == 698 ||
	            _x == 883 && _y == 740 || _x == 956 && _y == 782 ||
				_x == 1029 && _y == 824) {
				_direction = PLAYER_LEFT;
				_state = CHARA::STATE::LEFT_UP;
			}
		}
		if (g._gkey & PAD_INPUT_DOWN) {
			if (_x == 518 && _y == 530 || _x == 591 && _y == 572 ||
				_x == 664 && _y == 614 || _x == 737 && _y == 656 ||
				_x == 810 && _y == 698 || _x == 883 && _y == 740 || 
				_x == 956 && _y == 782) {
				_direction = PLAYER_RIGHT;
				_state = CHARA::STATE::RIGHT_DOWN;
			}
		}
		if (g._gkey & PAD_INPUT_RIGHT) {
			if (_x == 591 && _y == 572 || _x == 737 && _y == 656 ||
				_x == 883 && _y == 740 || _x == 1029 && _y == 824) {
				_direction = PLAYER_RIGHT;
				_state = CHARA::STATE::RIGHT_UP;
			}
		}
		if (g._gkey & PAD_INPUT_LEFT) {
			if (_x == 664 && _y == 530 || _x == 810 && _y == 614 ||
				_x == 956 && _y == 698 || _x == 1102 && _y == 782) {
				_direction = PLAYER_LEFT;
				_state = CHARA::STATE::LEFT_DOWN;
			}
		}
	}

	//ナス君落下処理
	if (_state == CHARA::STATE::FALL) {
		++_g;
		_y += _g;
		if (_y >= GROUND_Y) {
			_y = GROUND_Y;
			_state = CHARA::STATE::STOP;
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

	// 選択しているメニューを格納
	if (_x == 664 && _y == 530) {
		ModeTitle::_selectMenu = MODETITLE::SELECT::START;
	}
	else if (_x == 810 && _y == 614) {
		ModeTitle::_selectMenu = MODETITLE::SELECT::GAME_END;
	}
	else if (_x == 956 && _y == 698) {
		ModeTitle::_selectMenu = MODETITLE::SELECT::MELODY;
	}
	else if (_x == 1102 && _y == 782) {
		ModeTitle::_selectMenu = MODETITLE::SELECT::TUTORIAL;
	}
	else {
		ModeTitle::_selectMenu = MODETITLE::SELECT::UNSELECTED;
	}
}

void NasuTitle::Draw(Game& g)
{
	if (_direction == PLAYER_RIGHT) { DrawGraph(_x, _y, _cg[(_moveTime + 8) / 10], true); }
	if (_direction == PLAYER_LEFT) { DrawTurnGraph(_x, _y, _cg[(_moveTime + 8) / 10], true); }
}