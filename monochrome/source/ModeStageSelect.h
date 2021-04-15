/** 
 * @file   ModeStageSelect.h
 * @brief  �X�e�[�W�Z���N�g���[�h�N���X
 * 
 * @author matsuo tadahiko
 */

#include "ModeBase.h"
#include "StageSlide.h"
#include "NasuStageSelect.h"
#include "KyuriStageSelect.h"
#include "StageSyosai.h"

/**
 * @brief �X�e�[�W�Z���N�g���[�h�N���X
 */
class ModeStageSelect : public ModeBase{
	using base = ModeBase;

public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:
	static constexpr int PIANO_ALL = 6;                          // �s�A�m�u���b�N����
	const int PIANO_X[PIANO_ALL] = { 656,802,948,729,875,1021 }; // �s�A�m�u���b�NX���W
	const int PIANO_Y[2] = { 860,902 };                          // �s�A�m�u���b�NY���W
	static constexpr int MODORU_X = 40,   MODORU_Y = 960;        // �u���ǂ�v�\�����W
	static constexpr int KETTEI_X = 1640, KETTEI_Y = 960;        // �u�����Ă��v�\�����W
	static constexpr int MSMS_X = 1550;       // �T�C�g���\��X���W
	const int MSMS_Y[2] = { 10,60 };          // �T�C�g���\��Y���W

	int	_bg;               // �w�i
	int _cgPiano[2]; 	   // �s�A�m�u���b�N
	int	_cgModoru;	       // ���ǂ�UI
	int	_cgKettei;	  	   // �����Ă�UI
	int _cgMsms[2];        // BGM08���쌠���̃T�C�g��

	NasuStageSelect _nasuStageSelect;
	KyuriStageSelect _kyuriStageSelect;
	StageSlide _stageSlide;
	StageSyosai _stageSyosai;
};