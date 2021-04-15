/** 
 * @file   game.cpp
 * @brief  �Q�[���{��
 * 
 * @author matsuo tadahiko
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include "DxLib.h"
#include "game.h"
#include "ResourceServer.h"
#include "ModeTitle.h"
#include "ModeAmgLogo.h"

Game::Game() :_gkey(0), _gTrg(0), _gFrameCount(0), _gStageNo(1), _gHasKyuri(false), _gHasLanding(false), _gHasGameEnd(false), _gMelodyTotal(0)
{
	//���KSE
	_se["do"] = ResourceServer::LoadSoundMem("res/sound/SE_do.mp3");        //�u�h�v�̉������[�h
	_se["re"] = ResourceServer::LoadSoundMem("res/sound/SE_re.mp3");        //�u���v�̉������[�h
	_se["mi"] = ResourceServer::LoadSoundMem("res/sound/SE_mi.mp3");        //�u�~�v�̉������[�h
	_se["fa"] = ResourceServer::LoadSoundMem("res/sound/SE_fa.mp3");        //�u�t�@�v�̉������[�h
	_se["so"] = ResourceServer::LoadSoundMem("res/sound/SE_so.mp3");        //�u�\�v�̉������[�h
	_se["ra"] = ResourceServer::LoadSoundMem("res/sound/SE_ra.mp3");        //�u���v�̉������[�h
	_se["si"] = ResourceServer::LoadSoundMem("res/sound/SE_si.mp3");        //�u�V�v�̉������[�h
	_se["do_1"] = ResourceServer::LoadSoundMem("res/sound/SE_do_1oku.mp3"); //�u�h��1�I�N�^�[�u��v�̉������[�h
	_se["re_1"] = ResourceServer::LoadSoundMem("res/sound/SE_re_1oku.mp3"); //�u����1�I�N�^�[�u��v�̉������[�h
	_se["mi_1"] = ResourceServer::LoadSoundMem("res/sound/SE_mi_1oku.mp3"); //�u�~��1�I�N�^�[�u��v�̉������[�h
	_se["fa_1"] = ResourceServer::LoadSoundMem("res/sound/SE_fa_1oku.mp3"); //�u�t�@��1�I�N�^�[�u��v�̉������[�h
	_se["so_1"] = ResourceServer::LoadSoundMem("res/sound/SE_so_1oku.mp3"); //�u�\��1�I�N�^�[�u��v�̉������[�h
	_se["ra_1"] = ResourceServer::LoadSoundMem("res/sound/SE_ra_1oku.mp3"); //�u����1�I�N�^�[�u��v�̉������[�h
	_se["si_1"] = ResourceServer::LoadSoundMem("res/sound/SE_si_1oku.mp3"); //�u�V��1�I�N�^�[�u��v�̉������[�h
	_se["do_2"] = ResourceServer::LoadSoundMem("res/sound/SE_do_2oku.mp3"); //�u�h��2�I�N�^�[�u��v�̉������[�h

	//���̑�SE
	_se["nyuusyu"] = ResourceServer::LoadSoundMem("res/sound/SE_nyuusyu.mp3");  // �L���E���N�l����
	_se["clear"]   = ResourceServer::LoadSoundMem("res/sound/SE_clear.mp3");    // �N���A��
	_se["over"]    = ResourceServer::LoadSoundMem("res/sound/SE_over.mp3");     // �I�[�o�[��
	_se["yakeru"]  = ResourceServer::LoadSoundMem("res/sound/SE_yakeru.mp3");   // �G�Ƃ̐ڐG��
	_se["kettei"]  = ResourceServer::LoadSoundMem("res/sound/SE_kettei.mp3");   // ����
	_se["modoru"]  = ResourceServer::LoadSoundMem("res/sound/SE_modoru.mp3");   // �L�����Z���A�߂�
	_se["sentaku"] = ResourceServer::LoadSoundMem("res/sound/SE_sentaku.mp3");  // �X�e�[�W�I��
	_se["slide1"]  = ResourceServer::LoadSoundMem("res/sound/SE_slide1.mp3");   // �X�e�[�W�I���X���C�h��
	_se["slide2"]  = ResourceServer::LoadSoundMem("res/sound/SE_slide2.mp3");   // �X�e�[�W�I���X���C�h�֎~��

	_se["bgm08"] = ResourceServer::LoadSoundMem("res/sound/BGM08.mp3");         // �S�[���o�����BGM
	ChangeVolumeSoundMem(180, _se["bgm08"]);

	_serverMode = new ModeServer(*this);

	ModeAmgLogo* modeAmgLogo = new ModeAmgLogo();
	_serverMode->Add(modeAmgLogo, 0, "AmgLogo");
}

Game::~Game()
{
	delete _serverMode;
	delete _mapChips;
}

void Game::Input()
{
	int keyold = _gkey;
	_gkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gkey ^ keyold) & _gkey; 
}

void Game::Process()
{
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();

	_gFrameCount++;
}

void Game::Draw()
{
	_serverMode->DrawInit();
	_serverMode->Draw();
	_serverMode->DrawFinish();
}