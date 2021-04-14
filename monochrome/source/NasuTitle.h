#pragma once

/**
 * @file NasuTitle.h
 * @brief �^�C�g����ʂł̃v���C���[�ړ�
 *
 * @date 2020-09-20
 * @author �������F
 * @author ��O�D�n(�ꕔ)
 */

#include "Game.h"

class NasuTitle
{
public:
	NasuTitle();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
	 * �i�X�N�ړ��A���[�V��������
	 * @param moveX X���W�ړ�����(�}�w��)
	 * @param moveY Y���W�ړ�����(�}�w��)
	 */
	void MoveMotion(int moveX, int moveY);

private:
	const int PLAYER_RIGHT = 1;    // �v���C���[�E��������
	const int PLAYER_LEFT = -1;    // �v���C���[����������
	const int BLOCK_MOVE_X = 73;   // �u���b�N�ړ�����(X���W)
	const int BLOCK_MOVE_Y = 42;   // �u���b�N�ړ�����(Y���W)
	const int GROUND_Y = 530;      // ���n�ʒu

	int _cg[4];       // �摜
	int _x, _y;       // ���W
	int _oldX, _oldY; // 1�O�̍��W
	int _g;           // �d�͉����x
	int _direction;   // ����
	int	_moveTime;	  // �ړ�����
	int _moveAll;     // ���ړ�����
	int _state;       // ���
};