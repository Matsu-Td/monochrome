
/**
 * @file Player.cpp
 * @brief �v���C���[�v�Z�A�`�揈��
 *
 * @date 2020-09-24
 * @author �������F
 */

#include <cmath>
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTutorial.h"

Player::Player(Game& g)
{
	_mh = MV1LoadModel("res/model/nasuidou.mv1");
	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);             
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);
	
	Init(g);
}

Player::~Player()
{
}

void Player::Init(Game& g)
{
	// �����ʒu
	switch (g._gStageNo) {
	case GAME::STAGENO::TUTORIAL:                   
		_x = 1; _z = 1; break;
	case GAME::STAGENO::ST1_1:
		_x = 9; _z = 1; break;
	case GAME::STAGENO::ST1_2:
	case GAME::STAGENO::ST2_2:
		_x = 7; _z = 7; break;
	case GAME::STAGENO::ST1_3:
		_x = 4; _z = 1; break;
	case GAME::STAGENO::ST2_1:
		_x = 7; _z = 9; break;
	case GAME::STAGENO::ST2_3:
		_x = 4; _z = 4; break;
	}

	_r = 40;
	_movx = 0;
	_movz = 0;
	_nowx = _x * BLOCKSIZE;   // �h�b�g�ړ��ɂ���
	_nowz = _z * BLOCKSIZE;   // �h�b�g�ړ��ɂ���
	_nowy = 3000;
	_spd = 3;
	_gameOverCnt = 0;
	_moveTime =  MOVE_FLAME;
	_state = CHARA::STATE::STOP;
	_g = 0;
	_alphaSwichCnt = 0;
	_delay = 29;
	_playTime = 0.0f;
	
}

/**
 * �v���C���[��ԁA�ړ�������ύX����
 */
void Player::MoveStateChange(Game& g, int movx, int movz, int stateAndDirection)
{
	// �ړ���Ƀu���b�N(�}�b�v)������Έړ�����
	if (g._gCharaMap[_z + movz][_x + movx] != 0) {
		_x += movx;
		_z += movz;
		_state = stateAndDirection;
		_direction = stateAndDirection;
		--ModeGame::_steps;
	}
}

/**
 * �v���C���[�ړ��A�A�j���[�V��������
 */
void Player::MoveMotion(int moveX, int moveZ)
{
	--_moveTime;
	_nowx += _spd * moveX;
	_nowz += _spd * moveZ;
	_playTime += 1.4f;       // �A�j���[�V�����Đ�
	if (_moveTime == 0) {
		_state = CHARA::STATE::STOP;
		_moveTime = MOVE_FLAME;
	}
}

void Player::Process(Game& g)
{
	ObjectBase::Process(g);
				
	if (_gameOverCnt > 0) {
		_gameOverCnt--;
		_alphaSwichCnt++;
		for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++) {
			if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::ENEMY) {
				if (_alphaSwichCnt <= 20) {
					(*ite)->_alpha = ALPHA_MAX;
				}
				else if (_alphaSwichCnt > 20 && _alphaSwichCnt <= 40) {
					(*ite)->_alpha = ALPHA_MIN;
				}
				else if (_alphaSwichCnt > 40) {
					_alphaSwichCnt = 0;
				}
			}
		}
		if (_gameOverCnt == 0) {
			StopSoundMem(g._se["nyuusyu"]);
			StopSoundMem(g._se["yakeru"]);
			StopSoundMem(g._se["bgm08"]);
			StopMusic();

			if (g._gStageNo != GAME::STAGENO::TUTORIAL) { 
				PlaySoundMem(g._se["over"], DX_PLAYTYPE_BACK);

				ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");
				modeGame->_stopObjProcess = true;
				ModeGameOver* modeGameOver = new ModeGameOver();
				g._serverMode->Add(modeGameOver, 1, "GameOver");
			}
			else {            // �`���[�g���A���̂�
				g._serverMode->Del(g._serverMode->Get("Game"));

				ModeGame* modeGame = new ModeGame();
				g._serverMode->Add(modeGame, 0, "Game");
				ModeTutorial* modeTutorial = (ModeTutorial*)g._serverMode->Get("Tutorial");
				modeTutorial->_cgNum -= 1;
			}
		}
		return;
	}

	// �c����� �[�� �ɂȂ�@�ˁ@�Q�[���I�[�o�[�@
	if (ModeGame::_steps <= 0) {
		_delay--;              
		if (_delay <= 0) {
			if (g._gHasKyuri == false) { _gameOverCnt = 150; }
			if (g._gHasKyuri == true) { _gameOverCnt = 60; }
		}
	}
	// �i�X�N��������
		++_g;
		_nowy -= _g;
		if (_nowy <= GROUND_Y) {
			_nowy = GROUND_Y;
			// �`���[�g���A���̂�
			if (g._gStageNo == GAME::STAGENO::TUTORIAL && g._gHasLanding != true) {
				// �Q�[�����[�h�̃I�u�W�F�N�g�������X�g�b�v
				ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");
				modeGame->_stopObjProcess = true;
			}
			g._gHasLanding = true;
		}

	// �ړ�����
	if (_nowx % BLOCKSIZE == 0 && _nowz % BLOCKSIZE == 0) {
		_x = _nowx / BLOCKSIZE;
		_z = _nowz / BLOCKSIZE;
	}
	
	if (_state == CHARA::STATE::STOP && g._gHasLanding == true) {
		if (g._gkey & PAD_INPUT_LEFT && !(g._gkey & PAD_INPUT_UP) && !(g._gkey & PAD_INPUT_DOWN)) {
			_movx = 0;
			_movz = -1;
			MoveStateChange(g, _movx, _movz, CHARA::STATE::LEFT_DOWN);
		}
		if (g._gkey & PAD_INPUT_DOWN && !(g._gkey & PAD_INPUT_LEFT) && !(g._gkey & PAD_INPUT_RIGHT)) {
			_movx = 1;
			_movz = 0;
			MoveStateChange(g, _movx, _movz, CHARA::STATE::RIGHT_DOWN);
		}
		if (g._gkey & PAD_INPUT_UP && !(g._gkey & PAD_INPUT_LEFT) && !(g._gkey & PAD_INPUT_RIGHT)) {
			_movx = -1;
			_movz = 0;
			MoveStateChange(g, _movx, _movz, CHARA::STATE::LEFT_UP);
		}
		if (g._gkey & PAD_INPUT_RIGHT && !(g._gkey & PAD_INPUT_UP) && !(g._gkey & PAD_INPUT_DOWN)) {
			_movx = 0;
			_movz = 1;
			MoveStateChange(g, _movx, _movz, CHARA::STATE::RIGHT_UP);
		}
	}

	switch (_state) {
	case CHARA::STATE::LEFT_DOWN:
		MoveMotion(0, -1); break;
	case CHARA::STATE::RIGHT_DOWN:
		MoveMotion(1, 0); break;
	case CHARA::STATE::LEFT_UP:
		MoveMotion(-1, 0); break;
	case CHARA::STATE::RIGHT_UP:
		MoveMotion(0, 1); break;
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ�0�ɖ߂�
	if (_playTime >= _totalTime){
		_playTime = 0.0f;
	}

	// �i�X�N�ƃt���C�p��(�G)�̓����蔻��
	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++){
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::ENEMYABCD){
			if (IsHit(*(*ite)) == true){
				Damage(g);	
			}
		}
	}

	// �L���E���N�l����A�S�[���o���ʒu���ړ��\�ɂ���
	if (g._gHasKyuri == true) {
		switch (g._gStageNo) {
		case GAME::STAGENO::TUTORIAL:            
			g._gCharaMap[7][8] = 1; break;
		case GAME::STAGENO::ST1_1:
			g._gCharaMap[5][2] = 1; break;
		case GAME::STAGENO::ST1_2:
			g._gCharaMap[4][0] = 1; break;
		case GAME::STAGENO::ST1_3:
			g._gCharaMap[0][2] = 1; break;
		case GAME::STAGENO::ST2_1:
			g._gCharaMap[4][1] = 1; break;
		case GAME::STAGENO::ST2_2:
			g._gCharaMap[1][0] = 1; break;
		case GAME::STAGENO::ST2_3:
			g._gCharaMap[8][3] = 1; break;
		} 
	}
}

void Player::Draw(Game& g)
{
	float size = 18.0f;
	MV1SetScale(_mh, VGet(size, size, size));

	// �i�X�N���f�������ؑ�
	if (_direction == CHARA::STATE::RIGHT_DOWN) {  // �E���ړ�
		MV1SetRotationXYZ(_mh, VGet(0.0f, DX_PI_F, 0.0f));
	}
	if (_direction == CHARA::STATE::LEFT_UP) {     // ����ړ�
		 MV1SetRotationXYZ(_mh, VGet(0.0f, 0.0f, 0.0f));
	}
	if (_direction == CHARA::STATE::RIGHT_UP) {    // �E��ړ�
		MV1SetRotationXYZ(_mh, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
	}
	if (_direction == CHARA::STATE::LEFT_DOWN) {   // �����ړ�
		MV1SetRotationXYZ(_mh, VGet(0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f));
	}
	
	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);  
	MV1SetPosition(_mh, VGet(static_cast<float>(_nowx), static_cast<float>(_nowy), static_cast<float>(_nowz)));      // �`��ʒu�w��
	MV1DrawModel(_mh);                                     
}

void Player::Damage(Game& g)
{
	PlaySoundMem(g._se["yakeru"], DX_PLAYTYPE_BACK);
	if (g._gHasKyuri == false) { _gameOverCnt = 150; }
	if (g._gHasKyuri == true) { _gameOverCnt = 60; }
	//���S����
	MV1DeleteModel(_mh);
}