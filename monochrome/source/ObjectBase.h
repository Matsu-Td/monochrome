/** 
 * @file   ObjectBase.h
 * @brief  オブジェクト基底クラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "DxLib.h"
#include "mapchips.h"

class Game;

/**
 * @brief オブジェクト基底クラス
 */
class ObjectBase{
public:
	ObjectBase();
	~ObjectBase();

	enum class OBJECTTYPE {
		PLAYER,
		ENEMY,
		ENEMYABCD,
		GOAL,
		NOTE,
		CAMERA,
	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual void Init();
	virtual void Process(Game& g);
	virtual void Draw(Game& g);

	virtual bool IsHit(ObjectBase& o);
	virtual void Damage(Game& g){}

	void SetPosition(int x, int y, int z) { _x = x; _y = y; _z = z; }
	int GetX() const { return _x; }
	int GetY() const { return _y; }
	int GetZ() const { return _z; }
	int GetNowX() const { return _nowx; }
	int GetNowY() const { return _nowy; }
	int GetNowZ() const { return _nowz; }

	int _alpha;        // αブレンド

protected:
	int	_cg;		   // 画像
	int	_cgNum;		   // 使う画像枚数
	int _direction;    // 向き
	int	_cut;		   // 動作カウンタ
	int _mh;           // 3Dモデルハンドル
	int _attachIndex;  // アニメーションをアタッチ
	float _totalTime;  // アニメーション総再生時間
	float _playTime;   // アニメーション再生時間
	
	int _x, _y, _z;	         // 位置
	int _movx, _movz;        // 移動先の座標
	int _nowx, _nowy, _nowz; // 現在の座標
	int _spd;                // 移動速度
	int _r;                  // 半径(当たり判定用)
	VECTOR Pos;

	static const int BLOCKSIZE = 90;  // ブロックのサイズ
};
