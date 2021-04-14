#pragma once

/**
 * @file ModeServer.h
 * @brief ���[�h�Ǘ��T�[�o�[
 *
 * @date 2020-08-01
 * @author �������F
 */

#include <list>
#include "ModeBase.h"

class Game;

class	ModeServer
{
	using lstModeBase = std::list<ModeBase*>;

public:
	ModeServer(Game& g);
	virtual	~ModeServer();
	static ModeServer* _lpInstance;
	static ModeServer* GetInstance() { return (ModeServer*)_lpInstance; }

	int Add(ModeBase* mode, int layer, const char* name);
	int Del(ModeBase* mode);		// �폜�\��
	ModeBase* Get(int uid);
	ModeBase* Get(const char* name);
	int GetId(ModeBase* mode);
	int GetId(const char* name);
	const char* GetName(ModeBase* mode);
	const char* GetName(int uid);
	void Clear();
	int	LayerTop() { return INT32_MAX; }

	static bool modeSort(const ModeBase* x, const ModeBase* y) {
		return x->_layer < y->_layer;
	}
	// �v���Z�X���񂷂��߂̏�����
	int ProcessInit();	 
	// ���C���[�̏�̕����珈��
	int Process();	
	// �v���Z�X���񂵂���̌�n��
	int ProcessFinish();    

	// �`����񂷂��߂̏�����
	int DrawInit();		 
	// ���C���[�̉��̕����珈��
	int Draw();		    
	// �`����񂵂���̌�n��
	int DrawFinish();		

	// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�������Ă΂Ȃ�
	int SkipProcessUnderLayer();
	// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�`����Ă΂Ȃ�
	int SkipDrawUnderLayer();			
	// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A���Ԍo�߂��~�߂�
	int PauseProcessUnderLayer();		

private:
	int Release(ModeBase* mode);		// �폜��delete
	bool IsDelRegist(ModeBase* mode);	// �폜�\�񂳂�Ă��邩�H
	bool IsAdd(ModeBase* mode);		    // ���X�g�ɂ��邩�H


public:
	Game& _game;


private:
	lstModeBase		_vMode;			// ���[�h���X�g
	int				_uid_count;		// uid�J�E���^
	lstModeBase		_vModeAdd;		// �ǉ��\��
	lstModeBase		_vModeDel;		// �폜�\��

	ModeBase* _nowMode;	        	// ���݌Ăяo�����̃��[�h
	ModeBase* _skipProcessMode;	    // ���̃��[�h��艺��Process���Ă΂Ȃ�
	ModeBase* _skipDrawMode;	    // ���̃��[�h��艺��Draw���Ă΂Ȃ�
	ModeBase* _pauseProcessMode;	// ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�

};