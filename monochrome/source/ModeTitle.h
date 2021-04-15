/** 
 * @file   ModeTitle.h
 * @brief  �^�C�g�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @author iwamae soma
 */

#include "ModeBase.h"
#include "NasuTitle.h"
#include "MelodyTitle.h"

namespace MODETITLE {
	enum SELECT {
		UNSELECTED, // ���I���̏��
		START,      // ���j���[�F�͂��߂�
		GAME_END,   // ���j���[�F�����
		MELODY,     // ���j���[�F�����f�B
		TUTORIAL,   // ���j���[�F�`���[�g���A��
	};
}

/**
 * @brief �^�C�g�����[�h�N���X
 */
class ModeTitle : public ModeBase{
	using base = ModeBase;

public:
	bool Initialize(Game& g);
	bool Terminate(Game& g);
	bool Process(Game& g);
	bool Draw(Game& g);

	static int _selectMenu;  // �I�����Ă��郁�j���[���i�[

private:
	static constexpr int CG_TITLE_X = 480, CG_TITLE_Y = 270;      // �^�C�g�������W
	static constexpr int CG_KETTEI_X = 1640, CG_KETTEI_Y = 960;   // �����Ă��摜���W
	static constexpr int CG_SSGID_X = 1560, CG_SSGID_Y = 50;      // ����K�C�h���W

	static constexpr int CG_PIANO_ALL = 12;   // �s�A�m�u���b�N�\������
	const int CG_PIANO_X[CG_PIANO_ALL] = { 664,810,956,1102,518,591,664,737,810,883,956,1029 };  // �s�A�m�u���b�NX���W
	const int CG_PIANO_Y[CG_PIANO_ALL] = { 603,687,771,855,603,645,687,729,771,813,855,897 };    // �s�A�m�u���b�NY���W

	static constexpr int UI_ALL = 4;                  // UI(���j���[)����
	const int UI_POS_Y[UI_ALL] = { 470,550,630,630 }; // UI(���j���[)Y���W

	int _bg;           // �w�i

	int	_cgTitle;	   // �^�C�g����
	int _cgKettei;     // �����Ă�
	int _cgUi[UI_ALL]; // UI(���j���[)
	int _cgSsgid;      // ����K�C�h
	int _cgPiano[3];   // �s�A�m�u���b�N

	int _uix[4] = { 740,900,1040,1150 };  // ���j���[�I��pUI��x���W
	int _uiy[4] = { 470,550,630,630 };    // ���j���[�I��pUI��y���W
	int _sinCnt;            // �����A�j���[�V�����p�J�E���g

	NasuTitle _nasuTitle;
	MelodyTitle _melodyTitle;
};