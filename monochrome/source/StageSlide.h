/** 
 * @file   StageSlide.h
 * @brief  ステージ選択、スライド処理
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "game.h"

/**
 * @brief ステージ選択画面スライドクラス
 */
class StageSlide{
public:
	StageSlide();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
     * ステージスライド画像 左位置 ⇒ 真ん中へ移動 & サイズUP
     * @param slideNo ステージスライド番号(添字)
     */
	void SlidePatternA(int slideNo);

	/**
	 * ステージスライド画像 真ん中 ⇒ 左位置へ移動 & サイズDOWN
	 * @param slideNo ステージスライド番号(添字)
	 */
	void SlidePatternB(int slideNo);

	/**
	 * ステージスライド画像 真ん中 ⇒ 右位置へ移動 & サイズDOWN
	 * @param slideNo ステージスライド番号(添字)
	 */
	void SlidePatternC(int slideNo);

	/**
	 * ステージスライド画像 右位置 ⇒ 真ん中へ移動 & サイズUP
	 * @param slideNo ステージスライド番号(添字)
	 */
	void SlidePatternD(int slideNo);

	/**
	 * ステージスライド画像 左もしくは右へ移動(サイズ変更なし)
	 * @param slideNo ステージスライド番号(添字)
	 * @param direction 移動方向
	 */
	void SlidePatternE(int slideNo, int direction);

	static bool _slideState;      // スライドの状態(false：停止、true：スライド中)
	static int _oldStageNo;       // 1つ前に選択していたステージ番号

private:
	static constexpr int PAT_AB_DELTA_X = 522;         // ステージスライドX座標変化量：パターンA,B
	static constexpr int PAT_CD_DELTA_X = 878;         // ステージスライドX座標変化量：パターンC,D
	static constexpr int PAT_E_DELTA_X = 700;          // ステージスライドX座標変化量：パターンE
	static constexpr int DELTA_Y = 101;                // ステージスライドY座標変化量
	static constexpr int DELTA_W = 360, DELTA_H = 198; // ステージスライドサイズ変化量

	int _cgStage[6];	   // ステージスライド
	int _x[6] = { 552,1430,2130,2130,2130,2130 };      // ステージスライド画像x座標
	int _y[6] = { 97,198,198,198,198,198 };            // ステージスライド画像y座標
	int _w[6] = { 820,460,460,460,460,460 };           // ステージスライド画像横サイズ(画像拡縮用)
	int _h[6] = { 456,258,258,258,258,258 };           // ステージスライド画像縦サイズ(画像拡縮用)   
	int _oldX[6] = { 552,1430,2130,2130,2130,2130 };   // ステージスライド画像1つ前のx座標
	int _oldY[6] = { 97,198,198,198,198,198 };         // ステージスライド画像1つ前のy座標
	int _oldW[6] = { 820,460,460,460,460,460 };        // ステージスライド画像1つ前の横サイズ
	int _oldH[6] = { 456,258,258,258,258,258 };        // ステージスライド画像1つ前の縦サイズ
	int _slideCnt;                                     // スライドのカウント
	int _slideAll;                                     // スライド総カウント数
};