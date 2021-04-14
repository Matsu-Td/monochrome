#pragma once

/**
 * @file game.h
 * @brief �Q�[���{��
 *
 * @date 2020-09-24
 * @author �������F
 */

#include "ModeServer.h"
#include "ObjectServer.h"
#include "background.h"
#include "player.h"
#include "Enemy.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "EnemyC.h"
#include "EnemyD.h"
#include "Goal.h"
#include "Camera.h"
#include "mapchips.h"
#include "Note.h"
#include <unordered_map>

// ��ʐݒ�
constexpr auto SCREEN_W = 1920;    // ��ʂ̉��𑜓x
constexpr auto SCREEN_H = 1080;    // ��ʂ̏c�𑜓x
constexpr auto SCREEN_DEPTH = 32;  // 1�h�b�g������̃r�b�g��

namespace GAME {
	enum STAGENO {
		TUTORIAL,  // �`���[�g���A��
		ST1_1,     // �X�e�[�W1-1
		ST1_2,     // �X�e�[�W1-2
		ST1_3,     // �X�e�[�W1-3
		ST2_1,     // �X�e�[�W2-1
		ST2_2,     // �X�e�[�W2-2
		ST2_3,     // �X�e�[�W2-3
	};
}

namespace CHARA {
	enum STATE{  // �ړ��A�����̏��
		FALL,          // ����
		STOP,          // ��~
		RIGHT_DOWN,    // �E���ړ�
		LEFT_UP,       // ����ړ�
		RIGHT_UP,      // �E��ړ�
		LEFT_DOWN,     // �����ړ�
	};
}

class Game {
public:
	Game();             // �A�v���̏�����
	~Game();            // �A�v���̉��

	void Input();       // �t���[���������F����
	void Process();     // �t���[���������F�v�Z
	void Draw();        // �t���[���������F�`��

	// �Q�[�����
	int _gkey;                    // �L�[���͂̏��
	int _gTrg;                    // �L�[���͂̃g���K���
	int _gFrameCount;             // �}�C�t���[��+1����J�E���g
	int _gStageNo;                // �X�e�[�W�ԍ�
	int _gMelodyTotal;            // �����f�B�̂�����̓��萔�A���v
	bool _gHasKyuri;              // �L���E���N(����)�l���t���O(false�F���Atrue�F��)
	bool _gHasLanding;			  // �ړ��X�^�[�g�t���O(false�F�i�X�N���n�҂��Atrue�F�ړ��J�n)
	bool _gHasGameEnd;            // �Q�[���I���t���O(true�F�Q�[���I��)
	
	ModeServer *_serverMode;    
	ObjectServer _objServer;    
	MapChips* _mapChips;     
	
	std::unordered_map<std::string, int> _se;

	// �L�����}�b�v(JSON�}�b�v�f�[�^��ϊ�����)
	int _gCharaMap[14][11]{ 
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0
	};
};