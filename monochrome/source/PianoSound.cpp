/** 
 * @file   PianoSound.cpp
 * @brief  ステージ上音階再生処理クラス
 * 
 * @author matsuo tadahiko
 */

#include "DxLib.h"
#include "PianoSound.h"

/**
 * 音階の音量設定
 */
void PianoSound::VolumeCheck(Game& g, int enX, int enZ, int oldPlX, int oldPlZ)
{
	if (abs(enX - oldPlX) + abs(enZ - oldPlZ) <= 1) {        //プレイヤーとの距離が1マス以下
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
	else if (abs(enX - oldPlX) + abs(enZ - oldPlZ) <= 3) {     //プレイヤーとの距離が3マス以下
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
	else if (abs(enX - oldPlX) + abs(enZ - oldPlZ) <= 5) {    //プレイヤーとの距離が5マス以下
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
	else {                                                            //通常
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
 * 音階出力処理
 */
void PianoSound::SoundOutput(Game& g, int oldEnPos, int charaMap)
{
	//音階出力処理
	if (oldEnPos != charaMap) {   //現在位置と一歩前の位置が違う場合のみ
		switch (charaMap) {
		case 2:
			PlaySoundMem(g._se["do"], DX_PLAYTYPE_BACK); break;     //「ド」再生
		case 3:
			PlaySoundMem(g._se["re"], DX_PLAYTYPE_BACK); break;     //「レ」再生
		case 4:
			PlaySoundMem(g._se["mi"], DX_PLAYTYPE_BACK); break;     //「ミ」再生
		case 5:
			PlaySoundMem(g._se["fa"], DX_PLAYTYPE_BACK); break;     //「ファ」再生
		case 6:
			PlaySoundMem(g._se["so"], DX_PLAYTYPE_BACK); break;     //「ソ」再生
		case 7:
			PlaySoundMem(g._se["ra"], DX_PLAYTYPE_BACK); break;     //「ラ」再生
		case 8:
			PlaySoundMem(g._se["si"], DX_PLAYTYPE_BACK); break;     //「シ」再生
		case 9:
			PlaySoundMem(g._se["do_1"], DX_PLAYTYPE_BACK); break;   //「ドの1オクターブ上」再生
		case 10:
			PlaySoundMem(g._se["re_1"], DX_PLAYTYPE_BACK); break;   //「レの1オクターブ上」再生
		case 11:
			PlaySoundMem(g._se["mi_1"], DX_PLAYTYPE_BACK); break;   //「ミの1オクターブ上」再生
		case 12:
			PlaySoundMem(g._se["fa_1"], DX_PLAYTYPE_BACK); break;   //「ファの1オクターブ上」再生
		case 13:
			PlaySoundMem(g._se["so_1"], DX_PLAYTYPE_BACK); break;   //「ソの1オクターブ上」再生
		case 14:
			PlaySoundMem(g._se["ra_1"], DX_PLAYTYPE_BACK); break;   //「ラの1オクターブ上」再生
		case 15:
			PlaySoundMem(g._se["si_1"], DX_PLAYTYPE_BACK); break;   //「シの1オクターブ上」再生
		case 16:
			PlaySoundMem(g._se["do_2"], DX_PLAYTYPE_BACK); break;   //「ドの2オクターブ上」再生
		}
	}
}