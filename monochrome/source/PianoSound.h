#pragma once

/**
* @file PianoSound.h
* @brief �X�e�[�W�㉹�K�Đ�����
*
* @date 2020-09-24
* @author �������F
*/

#include "game.h"

class PianoSound
{
public:
	/**
	 * ���K�̉��ʐݒ�
	 * @param g �Q�[���N���X�Q��
	 * @param enX �G�̃u���b�N�ʒuX
	 * @param enZ �G�̃u���b�N�ʒuZ
	 * @param oldPlX �v���C���[���ړ�����O�̃u���b�N�ʒuX
	 * @param oldPlZ �v���C���[���ړ�����O�̃u���b�N�ʒuZ
	 */
	void VolumeCheck(Game& g, int enX, int enZ, int oldPlX, int oldPlZ);

	/**
	 * ���K�o�͏���
	 * @param g �Q�[���N���X�Q��
	 * @param oldEnPos �G�̈ړ�����O�̃u���b�N�ʒu
	 * @param charaMap �X�e�[�W�̃u���b�N�ʒu
	 */
	void SoundOutput(Game& g, int oldEnPos, int charaMap);

private:
	static constexpr int VOLUME_NOR = 100;  // ���ʁF�ʏ�(�l�F100)
	static constexpr int VOLUME_UP1 = 150;  // ���ʁF�v���C���[�Ƃ̋�����5�}�X�ȉ�(�l�F150)
	static constexpr int VOLUME_UP2 = 200;  // ���ʁF�v���C���[�Ƃ̋�����3�}�X�ȉ�(�l�F200)
	static constexpr int VOLUME_UP3 = 255;  // ���ʁF�v���C���[�Ƃ̋�����1�}�X�ȉ�(�l�F255)
};