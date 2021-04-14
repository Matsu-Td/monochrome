/**
 * @file   KyuriStageSelect.h
 * @brief  �X�e�[�W�I����ʂ̓G(�L���E���N)�\��
 * 
 * @author matsuo tadahiko
 * @date   2020/09/20
 */

#pragma once

#include "Game.h"

class KyuriStageSelect
{
public:
	KyuriStageSelect();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
	 * ��]�ړ����o����
	 */
	void Rotation();

private:
	static constexpr int GROUND_Y = 700;             // ���n�ʒu
	static constexpr int POS_X = 1400, POS_Y = 653;  // ��]�ړ����o�O���W
	static constexpr int DIF_X = 440, DIF_Y = 328;   // �ړ��ʒu�Ƃ̍�

	int _cg;           // �摜
	int _x, _y;        // ���W
	int _w, _h;        // �摜�T�C�Y
	int _g;            // �d�͉����x
	float _angle;      // ��]�l
	int _rotCnt;       // ��]������J�E���g
	int _cntAll;       // ���J�E���g��
};