#pragma once

/**
 * @file ModeServer.h
 * @brief モード管理サーバー
 *
 * @date 2020-08-01
 * @author 松尾忠彦
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
	int Del(ModeBase* mode);		// 削除予約
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
	// プロセスを回すための初期化
	int ProcessInit();	 
	// レイヤーの上の方から処理
	int Process();	
	// プロセスを回した後の後始末
	int ProcessFinish();    

	// 描画を回すための初期化
	int DrawInit();		 
	// レイヤーの下の方から処理
	int Draw();		    
	// 描画を回した後の後始末
	int DrawFinish();		

	// 現Processで、今処理しているレイヤーより下のレイヤーは、処理を呼ばない
	int SkipProcessUnderLayer();
	// 現Processで、今処理しているレイヤーより下のレイヤーは、描画を呼ばない
	int SkipDrawUnderLayer();			
	// 現Processで、今処理しているレイヤーより下のレイヤーは、時間経過を止める
	int PauseProcessUnderLayer();		

private:
	int Release(ModeBase* mode);		// 削除＆delete
	bool IsDelRegist(ModeBase* mode);	// 削除予約されているか？
	bool IsAdd(ModeBase* mode);		    // リストにあるか？


public:
	Game& _game;


private:
	lstModeBase		_vMode;			// モードリスト
	int				_uid_count;		// uidカウンタ
	lstModeBase		_vModeAdd;		// 追加予約
	lstModeBase		_vModeDel;		// 削除予約

	ModeBase* _nowMode;	        	// 現在呼び出し中のモード
	ModeBase* _skipProcessMode;	    // このモードより下はProcessを呼ばない
	ModeBase* _skipDrawMode;	    // このモードより下はDrawを呼ばない
	ModeBase* _pauseProcessMode;	// このモードより下はProcess時に時間経過をさせない

};