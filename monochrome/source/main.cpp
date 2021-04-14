
/**
 * @file main.cpp
 * @brief エントリーポイント
 *
 * @date 2020-07-16
 * @author 松尾忠彦
 */

#include "DxLib.h"
#include <stdio.h>
#include <time.h>
#include <memory>
#include "game.h"
#include "ResourceServer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ログの出力を行わない
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
		if (CheckHitKey(KEY_INPUT_ESCAPE)){  //エスケープキー入力でも終了
			break;
		}

		if (g->_gHasGameEnd) {               // タイトル「おわる」を選択
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
