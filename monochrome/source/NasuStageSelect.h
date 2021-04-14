#pragma once

/**
 * @file NasuStageSelect.h
 * @brief �X�e�[�W�I����ʂł̃v���C���[(�i�X�N)�ړ�����
 *
 * @date 2020-09-20
 * @author �������F
 */

#include "Game.h"

class NasuStageSelect
{
public:
	NasuStageSelect();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
	 * �i�X�N���,�X�e�[�W�ؑ֏���
	 * @param g �Q�[���N���X�Q��
	 * @param state ���
	 * @param direction �ړ�����
	 * @param nextStage ���̃X�e�[�W(�}�w��)
	 */
	void MoveStage(Game& g, int state, int direction, int nextStage);

	/**
	 * �i�X�N�ړ��A���[�V��������
	 * @param moveX X���W�ړ�����(�}�w��)
	 * @param moveY Y���W�ړ�����(�}�w��)
	 */
	void MoveMotion(int moveX, int moveY);

	/**
	 * ��]�ړ����W ��������
	 */
	void SubPosition();

	/**
	 * ��]�ړ����o����
	 */
	void Rotation();

private:
	static constexpr int PLAYER_RIGHT = 1;      // �v���C���[�E��������
	static constexpr int PLAYER_LEFT = 2;       // �v���C���[����������
	static constexpr int BLOCK_MOVE_X = 73;     // �u���b�N�ړ�����(X���W)
	static constexpr int BLOCK_MOVE_Y = 42;     // �u���b�N�ړ�����(Y���W)

	static constexpr int GROUND_Y = 853;        // ���n�ʒu
	static constexpr int ROT_CNT_ALL = 60;      // ����]�J�E���g��
	static constexpr int MOVE_POS_X = 960, MOVE_POS_Y = 325;   // �ŏI��]�ړ����W

	int _cg[4];          // �摜
	int _x, _y;          // ���W
	int _oldX, _oldY;    // 1�O�̍��W
	int _w, _h;          // �摜�T�C�Y
	int _direction;      // �摜�̌���
	int _g;              // �d�͉����x
	int	_moveTime;	     // �ړ�����
	int _all;            // ���ړ�����
	int _state;          // ���	
	int _rotX, _rotY;    // ��]���o�p���W
	float _angle;        // ��]�l
	int _subX, _subY;    // ���W - �X�e�[�W�X���C�h�摜���S���W
	int _rotCnt;         // ��]������J�E���g
};
