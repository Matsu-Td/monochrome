#pragma once

/**
 * @file StageSyosai.h
 * @brief �X�e�[�W�ڍו\��
 *
 * @date 2020-09-20
 * @author �������F
 */

#include "game.h"

class StageSyosai
{
public:
	StageSyosai();

	void Draw(Game& g);

private:
	static constexpr int SYOSAI_X = 680, SYOSAI_Y = 600;  // �X�e�[�W�ڍו\�����W
	static constexpr int BANGO_LX = 100;         // �X�e�[�W�ԍ��\��X���W(����)
	static constexpr int BANGO_RX = 1500;        // �X�e�[�W�ԍ��\��X���W(�E��)
	static constexpr int BANGO_Y = 480;          // �X�e�[�W�ԍ��\��Y���W

	int _cgStageBango[6];   // �X�e�[�W�ԍ�
	int _cgStageSyosai[6];  // �X�e�[�W�ڍ�
};