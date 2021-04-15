/** 
 * @file   PianoSound.cpp
 * @brief  �X�e�[�W�㉹�K�Đ������N���X
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "PianoSound.h"

/**
 * ���K�̉��ʐݒ�
 */
void PianoSound::VolumeCheck(Game& g, int enX, int enZ, int oldPlX, int oldPlZ)
{
	if (abs(enX - oldPlX) + abs(enZ - oldPlZ) <= 1) {        //�v���C���[�Ƃ̋�����1�}�X�ȉ�
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["do"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["re"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["mi"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["fa"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["so"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["ra"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["si"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["do_1"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["re_1"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["mi_1"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["fa_1"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["so_1"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["ra_1"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["si_1"]);
		ChangeVolumeSoundMem(VOLUME_UP3, g._se["do_2"]);
	}
	else if (abs(enX - oldPlX) + abs(enZ - oldPlZ) <= 3) {     //�v���C���[�Ƃ̋�����3�}�X�ȉ�
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["do"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["re"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["mi"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["fa"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["so"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["ra"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["si"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["do_1"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["re_1"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["mi_1"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["fa_1"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["so_1"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["ra_1"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["si_1"]);
		ChangeVolumeSoundMem(VOLUME_UP2, g._se["do_2"]);
	}
	else if (abs(enX - oldPlX) + abs(enZ - oldPlZ) <= 5) {    //�v���C���[�Ƃ̋�����5�}�X�ȉ�
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["do"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["re"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["mi"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["fa"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["so"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["ra"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["si"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["do_1"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["re_1"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["mi_1"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["fa_1"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["so_1"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["ra_1"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["si_1"]);
		ChangeVolumeSoundMem(VOLUME_UP1, g._se["do_2"]);
	}
	else {                                                            //�ʏ�
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["do"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["re"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["mi"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["fa"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["so"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["ra"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["si"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["do_1"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["re_1"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["mi_1"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["fa_1"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["so_1"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["ra_1"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["si_1"]);
		ChangeVolumeSoundMem(VOLUME_NOR, g._se["do_2"]);
	}
}

/**
 * ���K�o�͏���
 */
void PianoSound::SoundOutput(Game& g, int oldEnPos, int charaMap)
{
	//���K�o�͏���
	if (oldEnPos != charaMap) {   //���݈ʒu�ƈ���O�̈ʒu���Ⴄ�ꍇ�̂�
		switch (charaMap) {
		case 2:
			PlaySoundMem(g._se["do"], DX_PLAYTYPE_BACK); break;     //�u�h�v�Đ�
		case 3:
			PlaySoundMem(g._se["re"], DX_PLAYTYPE_BACK); break;     //�u���v�Đ�
		case 4:
			PlaySoundMem(g._se["mi"], DX_PLAYTYPE_BACK); break;     //�u�~�v�Đ�
		case 5:
			PlaySoundMem(g._se["fa"], DX_PLAYTYPE_BACK); break;     //�u�t�@�v�Đ�
		case 6:
			PlaySoundMem(g._se["so"], DX_PLAYTYPE_BACK); break;     //�u�\�v�Đ�
		case 7:
			PlaySoundMem(g._se["ra"], DX_PLAYTYPE_BACK); break;     //�u���v�Đ�
		case 8:
			PlaySoundMem(g._se["si"], DX_PLAYTYPE_BACK); break;     //�u�V�v�Đ�
		case 9:
			PlaySoundMem(g._se["do_1"], DX_PLAYTYPE_BACK); break;   //�u�h��1�I�N�^�[�u��v�Đ�
		case 10:
			PlaySoundMem(g._se["re_1"], DX_PLAYTYPE_BACK); break;   //�u����1�I�N�^�[�u��v�Đ�
		case 11:
			PlaySoundMem(g._se["mi_1"], DX_PLAYTYPE_BACK); break;   //�u�~��1�I�N�^�[�u��v�Đ�
		case 12:
			PlaySoundMem(g._se["fa_1"], DX_PLAYTYPE_BACK); break;   //�u�t�@��1�I�N�^�[�u��v�Đ�
		case 13:
			PlaySoundMem(g._se["so_1"], DX_PLAYTYPE_BACK); break;   //�u�\��1�I�N�^�[�u��v�Đ�
		case 14:
			PlaySoundMem(g._se["ra_1"], DX_PLAYTYPE_BACK); break;   //�u����1�I�N�^�[�u��v�Đ�
		case 15:
			PlaySoundMem(g._se["si_1"], DX_PLAYTYPE_BACK); break;   //�u�V��1�I�N�^�[�u��v�Đ�
		case 16:
			PlaySoundMem(g._se["do_2"], DX_PLAYTYPE_BACK); break;   //�u�h��2�I�N�^�[�u��v�Đ�
		}
	}
}