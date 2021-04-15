/** 
 * @file   ObjectBase.h
 * @brief  �I�u�W�F�N�g���N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "DxLib.h"
#include "mapchips.h"

class Game;

/**
 * @brief �I�u�W�F�N�g���N���X
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

	int _alpha;        // ���u�����h

protected:
	int	_cg;		   // �摜
	int	_cgNum;		   // �g���摜����
	int _direction;    // ����
	int	_cut;		   // ����J�E���^
	int _mh;           // 3D���f���n���h��
	int _attachIndex;  // �A�j���[�V�������A�^�b�`
	float _totalTime;  // �A�j���[�V�������Đ�����
	float _playTime;   // �A�j���[�V�����Đ�����
	
	int _x, _y, _z;	         // �ʒu
	int _movx, _movz;        // �ړ���̍��W
	int _nowx, _nowy, _nowz; // ���݂̍��W
	int _spd;                // �ړ����x
	int _r;                  // ���a(�����蔻��p)
	VECTOR Pos;

	static const int BLOCKSIZE = 90;  // �u���b�N�̃T�C�Y
};
