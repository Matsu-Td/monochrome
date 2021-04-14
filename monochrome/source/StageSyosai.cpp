
/**
 * @file StageSyosai.cpp
 * @brief ステージ詳細表示
 *
 * @date 2020-09-20
 * @author 松尾忠彦
 */

#include "DxLib.h"
#include "ResourceServer.h"
#include "StageSyosai.h"

StageSyosai::StageSyosai()
{
	_cgStageBango[0] = ResourceServer::LoadGraph("res/stagebango1-1.png");
	_cgStageBango[1] = ResourceServer::LoadGraph("res/stagebango1-2.png");
	_cgStageBango[2] = ResourceServer::LoadGraph("res/stagebango1-3.png");
	_cgStageBango[3] = ResourceServer::LoadGraph("res/stagebango2-1.png");
	_cgStageBango[4] = ResourceServer::LoadGraph("res/stagebango2-2.png");
	_cgStageBango[5] = ResourceServer::LoadGraph("res/stagebango2-3.png");

	_cgStageSyosai[0] = ResourceServer::LoadGraph("res/stagesyosai1-1.png");
	_cgStageSyosai[1] = ResourceServer::LoadGraph("res/stagesyosai1-2.png");
	_cgStageSyosai[2] = ResourceServer::LoadGraph("res/stagesyosai1-3.png");
	_cgStageSyosai[3] = ResourceServer::LoadGraph("res/stagesyosai2-1.png");
	_cgStageSyosai[4] = ResourceServer::LoadGraph("res/stagesyosai2-2.png");
	_cgStageSyosai[5] = ResourceServer::LoadGraph("res/stagesyosai2-3.png");
}

void StageSyosai::Draw(Game& g)
{
	switch (g._gStageNo) {
	case GAME::STAGENO::ST1_1:
		DrawGraph(BANGO_RX, BANGO_Y, _cgStageBango[1], TRUE);
		DrawGraph(SYOSAI_X, SYOSAI_Y, _cgStageSyosai[0], TRUE);
		break;
	case GAME::STAGENO::ST1_2:
		DrawGraph(BANGO_LX, BANGO_Y, _cgStageBango[0], TRUE);
		DrawGraph(BANGO_RX, BANGO_Y, _cgStageBango[2], TRUE);
		DrawGraph(SYOSAI_X, SYOSAI_Y, _cgStageSyosai[1], TRUE);
		break;
	case GAME::STAGENO::ST1_3:
		DrawGraph(BANGO_LX, BANGO_Y, _cgStageBango[1], TRUE);
		DrawGraph(BANGO_RX, BANGO_Y, _cgStageBango[3], TRUE);
		DrawGraph(SYOSAI_X, SYOSAI_Y, _cgStageSyosai[2], TRUE);
		break;
	case GAME::STAGENO::ST2_1:
		DrawGraph(BANGO_LX, BANGO_Y, _cgStageBango[2], TRUE);
		DrawGraph(BANGO_RX, BANGO_Y, _cgStageBango[4], TRUE);
		DrawGraph(SYOSAI_X, SYOSAI_Y, _cgStageSyosai[3], TRUE);
		break;
	case GAME::STAGENO::ST2_2:
		DrawGraph(BANGO_LX, BANGO_Y, _cgStageBango[3], TRUE);
		DrawGraph(BANGO_RX, BANGO_Y, _cgStageBango[5], TRUE);
		DrawGraph(SYOSAI_X, SYOSAI_Y, _cgStageSyosai[4], TRUE);
		break;
	case GAME::STAGENO::ST2_3:
		DrawGraph(BANGO_LX, BANGO_Y, _cgStageBango[4], TRUE);
		DrawGraph(SYOSAI_X, SYOSAI_Y, _cgStageSyosai[5], TRUE);
		break;
	}
}

