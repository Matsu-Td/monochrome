/** 
 * @file   StageSlide.h
 * @brief  �X�e�[�W�I���A�X���C�h����
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "game.h"

/**
 * @brief �X�e�[�W�I����ʃX���C�h�N���X
 */
class StageSlide{
public:
	StageSlide();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

	/**
     * �X�e�[�W�X���C�h�摜 ���ʒu �� �^�񒆂ֈړ� & �T�C�YUP
     * @param slideNo �X�e�[�W�X���C�h�ԍ�(�Y��)
     */
	void SlidePatternA(int slideNo);

	/**
	 * �X�e�[�W�X���C�h�摜 �^�� �� ���ʒu�ֈړ� & �T�C�YDOWN
	 * @param slideNo �X�e�[�W�X���C�h�ԍ�(�Y��)
	 */
	void SlidePatternB(int slideNo);

	/**
	 * �X�e�[�W�X���C�h�摜 �^�� �� �E�ʒu�ֈړ� & �T�C�YDOWN
	 * @param slideNo �X�e�[�W�X���C�h�ԍ�(�Y��)
	 */
	void SlidePatternC(int slideNo);

	/**
	 * �X�e�[�W�X���C�h�摜 �E�ʒu �� �^�񒆂ֈړ� & �T�C�YUP
	 * @param slideNo �X�e�[�W�X���C�h�ԍ�(�Y��)
	 */
	void SlidePatternD(int slideNo);

	/**
	 * �X�e�[�W�X���C�h�摜 ���������͉E�ֈړ�(�T�C�Y�ύX�Ȃ�)
	 * @param slideNo �X�e�[�W�X���C�h�ԍ�(�Y��)
	 * @param direction �ړ�����
	 */
	void SlidePatternE(int slideNo, int direction);

	static bool _slideState;      // �X���C�h�̏��(false�F��~�Atrue�F�X���C�h��)
	static int _oldStageNo;       // 1�O�ɑI�����Ă����X�e�[�W�ԍ�

private:
	static constexpr int PAT_AB_DELTA_X = 522;         // �X�e�[�W�X���C�hX���W�ω��ʁF�p�^�[��A,B
	static constexpr int PAT_CD_DELTA_X = 878;         // �X�e�[�W�X���C�hX���W�ω��ʁF�p�^�[��C,D
	static constexpr int PAT_E_DELTA_X = 700;          // �X�e�[�W�X���C�hX���W�ω��ʁF�p�^�[��E
	static constexpr int DELTA_Y = 101;                // �X�e�[�W�X���C�hY���W�ω���
	static constexpr int DELTA_W = 360, DELTA_H = 198; // �X�e�[�W�X���C�h�T�C�Y�ω���

	int _cgStage[6];	   // �X�e�[�W�X���C�h
	int _x[6] = { 552,1430,2130,2130,2130,2130 };      // �X�e�[�W�X���C�h�摜x���W
	int _y[6] = { 97,198,198,198,198,198 };            // �X�e�[�W�X���C�h�摜y���W
	int _w[6] = { 820,460,460,460,460,460 };           // �X�e�[�W�X���C�h�摜���T�C�Y(�摜�g�k�p)
	int _h[6] = { 456,258,258,258,258,258 };           // �X�e�[�W�X���C�h�摜�c�T�C�Y(�摜�g�k�p)   
	int _oldX[6] = { 552,1430,2130,2130,2130,2130 };   // �X�e�[�W�X���C�h�摜1�O��x���W
	int _oldY[6] = { 97,198,198,198,198,198 };         // �X�e�[�W�X���C�h�摜1�O��y���W
	int _oldW[6] = { 820,460,460,460,460,460 };        // �X�e�[�W�X���C�h�摜1�O�̉��T�C�Y
	int _oldH[6] = { 456,258,258,258,258,258 };        // �X�e�[�W�X���C�h�摜1�O�̏c�T�C�Y
	int _slideCnt;                                     // �X���C�h�̃J�E���g
	int _slideAll;                                     // �X���C�h���J�E���g��
};