
/**
 * @file main.cpp
 * @brief �G���g���[�|�C���g
 *
 * @date 2020-07-16
 * @author �������F
 */

#include "DxLib.h"
#include <stdio.h>
#include <time.h>
#include <memory>
#include "game.h"
#include "ResourceServer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���O�̏o�͂��s��Ȃ�
	SetOutApplicationLogValidFlag(false);

	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	
	ChangeWindowMode(false);						
	if (DxLib_Init() == -1)
	{	
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	srand((unsigned int)time(NULL));

	ResourceServer::Init();

	auto g = std::make_unique<Game>();

	while (ProcessMessage() == 0){
		if (CheckHitKey(KEY_INPUT_ESCAPE)){  //�G�X�P�[�v�L�[���͂ł��I��
			break;
		}

		if (g->_gHasGameEnd) {               // �^�C�g���u�����v��I��
			break;
		}

		g->Input();	
		g->Process();
		g->Draw();
	}

	ResourceServer::Release();
	
	DxLib_End();

	return 0;
}
