#pragma once

/**
* @file PianoSound.h
* @brief ステージ上音階再生処理
*
* @date 2020-09-24
* @author 松尾忠彦
*/

#include "game.h"

class PianoSound
{
public:
	/**
	 * 音階の音量設定
	 * @param g ゲームクラス参照
	 * @param enX 敵のブロック位置X
	 * @param enZ 敵のブロック位置Z
	 * @param oldPlX プレイヤーが移動する前のブロック位置X
	 * @param oldPlZ プレイヤーが移動する前のブロック位置Z
	 */
	void VolumeCheck(Game& g, int enX, int enZ, int oldPlX, int oldPlZ);

	/**
	 * 音階出力処理
	 * @param g ゲームクラス参照
	 * @param oldEnPos 敵の移動する前のブロック位置
	 * @param charaMap ステージのブロック位置
	 */
	void SoundOutput(Game& g, int oldEnPos, int charaMap);

private:
	static constexpr int VOLUME_NOR = 100;  // 音量：通常(値：100)
	static constexpr int VOLUME_UP1 = 150;  // 音量：プレイヤーとの距離が5マス以下(値：150)
	static constexpr int VOLUME_UP2 = 200;  // 音量：プレイヤーとの距離が3マス以下(値：200)
	static constexpr int VOLUME_UP3 = 255;  // 音量：プレイヤーとの距離が1マス以下(値：255)
};