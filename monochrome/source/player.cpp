
/**
 * @file Player.cpp
 * @brief プレイヤー計算、描画処理
 *
 * @date 2020-09-24
 * @author 松尾忠彦
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
	// 初期位置
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
	_nowx = _x * BLOCKSIZE;   // ドット移動にする
	_nowz = _z * BLOCKSIZE;   // ドット移動にする
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
 * プレイヤー状態、移動方向を変更する
 */
void Player::MoveStateChange(Game& g, int movx, int movz, int stateAndDirection)
{
	// 移動先にブロック(マップ)があれば移動する
	if (g._gCharaMap[_z + movz][_x + movx] != 0) {
		_x += movx;
		_z += movz;
		_state = stateAndDirection;
		_direction = stateAndDirection;
		--ModeGame::_steps;
	}
}

/**
 * プレイヤー移動、アニメーション処理
 */
void Player::MoveMotion(int moveX, int moveZ)
{
	--_moveTime;
	_nowx += _spd * moveX;
	_nowz += _spd * moveZ;
	_playTime += 1.4f;       // アニメーション再生
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
			else {            // チュートリアルのみ
				g._serverMode->Del(g._serverMode->Get("Game"));

				ModeGame* modeGame = new ModeGame();
				g._serverMode->Add(modeGame, 0, "Game");
				ModeTutorial* modeTutorial = (ModeTutorial*)g._serverMode->Get("Tutorial");
				modeTutorial->_cgNum -= 1;
			}
		}
		return;
	}

	// 残り歩数 ゼロ になる　⇒　ゲームオーバー　
	if (ModeGame::_steps <= 0) {
		_delay--;              
		if (_delay <= 0) {
			if (g._gHasKyuri == false) { _gameOverCnt = 150; }
			if (g._gHasKyuri == true) { _gameOverCnt = 60; }
		}
	}
	// ナス君落下処理
		++_g;
		_nowy -= _g;
		if (_nowy <= GROUND_Y) {
			_nowy = GROUND_Y;
			// チュートリアルのみ
			if (g._gStageNo == GAME::STAGENO::TUTORIAL && g._gHasLanding != true) {
				// ゲームモードのオブジェクト処理をストップ
				ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");
				modeGame->_stopObjProcess = true;
			}
			g._gHasLanding = true;
		}

	// 移動処理
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

	// 再生時間がアニメーションの総再生時間に達したら再生時間を0に戻す
	if (_playTime >= _totalTime){
		_playTime = 0.0f;
	}

	// ナス君とフライパン(敵)の当たり判定
	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++){
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::ENEMYABCD){
			if (IsHit(*(*ite)) == true){
				Damage(g);	
			}
		}
	}

	// キュウリ君獲得後、ゴール出現位置を移動可能にする
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

	// ナス君モデル向き切替
	if (_direction == CHARA::STATE::RIGHT_DOWN) {  // 右下移動
		MV1SetRotationXYZ(_mh, VGet(0.0f, DX_PI_F, 0.0f));
	}
	if (_direction == CHARA::STATE::LEFT_UP) {     // 左上移動
		 MV1SetRotationXYZ(_mh, VGet(0.0f, 0.0f, 0.0f));
	}
	if (_direction == CHARA::STATE::RIGHT_UP) {    // 右上移動
		MV1SetRotationXYZ(_mh, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
	}
	if (_direction == CHARA::STATE::LEFT_DOWN) {   // 左下移動
		MV1SetRotationXYZ(_mh, VGet(0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f));
	}
	
	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);  
	MV1SetPosition(_mh, VGet(static_cast<float>(_nowx), static_cast<float>(_nowy), static_cast<float>(_nowz)));      // 描画位置指定
	MV1DrawModel(_mh);                                     
}

void Player::Damage(Game& g)
{
	PlaySoundMem(g._se["yakeru"], DX_PLAYTYPE_BACK);
	if (g._gHasKyuri == false) { _gameOverCnt = 150; }
	if (g._gHasKyuri == true) { _gameOverCnt = 60; }
	//死亡処理
	MV1DeleteModel(_mh);
}