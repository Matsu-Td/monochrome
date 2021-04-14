
/**
 * @file Mode_LightMap.cpp
 * @brief ���C�g�}�b�v����(�Ó])
 *
 * @date 2020-09-24
 * @author �������F
 */

#include "DxLib.h"
#include "Mode_LightMap.h"
#include "game.h"
#include "ResourceServer.h"
#include "ModeGame.h"

bool Mode_LightMap::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	// ���C�g�̈ʒu,�T�C�Y
	_px = DISP_W / 2;
	_py = DISP_H / 2 - 200;
	_psize = 1080;

	return true;
}

bool Mode_LightMap::Terminate(Game& g) 
{
	base::Terminate(g);
	return true;
}

void Mode_LightMap::SpotLight(int cx, int cy, int cr)
{
	int x, y;

	// pixel�P�ʂ���}�b�v�P�ʂɕϊ�
	cx /= LIGHTSIZE_W;
	cy /= LIGHTSIZE_H;
	cr /= LIGHTSIZE_W;

	for (y = cy - cr; y < cy + cr; y++) {
		if (0 <= y && y < LIGHTMAP_H) {	            // �}�b�v���ɓ����Ă��邩
			for (x = cx - cr; x < cx + cr; x++) {
				if (0 <= x && x < LIGHTMAP_W) {		// �}�b�v���ɓ����Ă��邩

					// ���S���W(cx,cy)����̋��������߁A�A���t�@�l�����߂�
					int len = (int)(((cx - x) * (cx - x) + (cy - y) * (cy - y)));

					int alpha = len * 255 / (cr * cr);
					if (alpha > 255) { alpha = 255; }

					// �A���t�@�̒l�Ō���������
					_mapLight[y * LIGHTMAP_W + x] = alpha;

				}
			}
		}
	}
}

bool Mode_LightMap::Process(Game& g)
{
	base::Process(g);
	
	// ���C�g�}�b�v�S�̂���(255)�ɂ���
	int x, y;
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			_mapLight[y * LIGHTMAP_W + x] = 255;
		}
	}
	
	_psize -= 18;
	if (_psize < 0) { _psize = 0; }
	if (_psize == 0) {
		g._serverMode->Del(this);
		g._serverMode->Del(g._serverMode->Get("StageSelect"));

		ModeGame* modeGame = new ModeGame();                        //�Q�[����ʂֈړ�
		g._serverMode->Add(modeGame, 0, "Game");
	}
	// �X�|�b�g���C�g
	SpotLight(_px, _py, _psize);


	return true;
}

bool Mode_LightMap::Draw(Game& g) 
{
	base::Draw(g);

	// ���C�g�}�b�v���ォ�甼�����`��
	int x, y;
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _mapLight[y * LIGHTMAP_W + x]);
			DrawBox(x * LIGHTSIZE_W, y * LIGHTSIZE_H, x * LIGHTSIZE_W + LIGHTSIZE_W, y * LIGHTSIZE_H + LIGHTSIZE_H, GetColor(0, 0, 0), TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return true;
}