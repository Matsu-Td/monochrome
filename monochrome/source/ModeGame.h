
/**
 * @file ModeGame.h
 * @brief �Q�[�����[�h
 *
 * @date 2020-09-20
 * @author �������F
 */

#include "ModeBase.h"
#include "ObjectServer.h"
#include "background.h"
#include "player.h"
#include "Enemy.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "EnemyC.h"
#include "EnemyD.h"
#include "Goal.h"
#include "Note.h"
#include "Camera.h"

class ModeGame : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	bool _stopObjProcess;       // �I�u�W�F�N�g�������X�g�b�v
	static int _steps;          // ����

private:
	static constexpr int STEPS_TUTORIAL = 40;  // �������F�`���[�g���A��
	static constexpr int STEPS1_1 = 40;        // �������F�X�e�[�W1-1
	static constexpr int STEPS1_2 = 30;        // �������F�X�e�[�W1-2
	static constexpr int STEPS1_3 = 45;        // �������F�X�e�[�W1-3
	static constexpr int STEPS2_1 = 35;        // �������F�X�e�[�W2-1
	static constexpr int STEPS2_2 = 30;        // �������F�X�e�[�W2-2
	static constexpr int STEPS2_3 = 35;        // �������F�X�e�[�W2-3

	// �摜�`����W  =  {�̂���, AHS�ȈՕ\��, ����K�C�h, ����10�̈�, ����1�̈� }
	const int CG_POS_X[5] = { 1500,120,1560,1660,1720 };
	const int CG_POS_Y[5] = { 920,360,50,920,920 };

protected:
	BackGround _bg;       // �w�i

	int _cg[3];           // �摜
	int _cgSteps[10];     // �����\���p�̉摜
};