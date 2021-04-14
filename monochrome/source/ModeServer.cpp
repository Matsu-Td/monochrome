
/**
 * @file ModeServer.cpp
 * @brief モード管理サーバー
 *
 * @date 2020-08-01
 * @author 松尾忠彦
 */

#include <cstddef>
#include "DxLib.h"
#include "ModeServer.h"

ModeServer* ModeServer::_lpInstance = NULL;

ModeServer::ModeServer(Game& g) : _game(g)
{
	_lpInstance = this;
	_uid_count = 1;
	_nowMode = NULL;
	_skipProcessMode = NULL;
	_skipDrawMode = NULL;
	_pauseProcessMode = NULL;
}

ModeServer::~ModeServer()
{
	Clear();
	_lpInstance = NULL;
}


int ModeServer::Add(ModeBase* mode, int layer, const char* name) {
	_vModeAdd.push_back(mode);		// 登録予約
	mode->_uid = _uid_count;
	_uid_count++;
	mode->_layer = layer;
	mode->_szName = name;
	return mode->_uid;
}

// 削除予約
int ModeServer::Del(ModeBase* mode) {
	_vModeDel.push_back(mode);
	return 0;
}

// 削除＆delete
int ModeServer::Release(ModeBase* mode) {
	lstModeBase::iterator ite = _vMode.begin();
	for (; ite != _vMode.end(); ) {
		if ((*ite) == mode) {
			(*ite)->Terminate(_game);
			delete (*ite);
			ite = _vMode.erase(ite);
		}
		else {
			++ite;
		}
	}
	return 1;
}

// 全部削除
void ModeServer::Clear() {
	lstModeBase::reverse_iterator ite = _vMode.rbegin();
	for (; ite != _vMode.rend(); ++ite) {
		(*ite)->Terminate(_game);
		delete (*ite);
	}
	lstModeBase::iterator iteAdd = _vModeAdd.begin();
	for (; iteAdd != _vModeAdd.end(); ++iteAdd) {
		(*iteAdd)->Terminate(_game);
		delete (*iteAdd);
	}
	_vMode.clear();
	_vModeAdd.clear();
	_vModeDel.clear();
}



// 削除予約されているか
bool ModeServer::IsDelRegist(ModeBase* mode) {
	if (_vModeDel.size() > 0) {
		lstModeBase::iterator iteDel = _vModeDel.begin();
		for (; iteDel != _vModeDel.end(); ++iteDel) {
			if ((*iteDel) == mode) { return true; }
		}
	}
	return false;
}

// モードリストにあるか
bool ModeServer::IsAdd(ModeBase* mode) {
	// 登録中のもの、登録予約中のものから検索する
	lstModeBase::iterator ite;
	ite = _vMode.begin();
	for (; ite != _vMode.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite) == mode) { return true; }
	}
	ite = _vModeAdd.begin();
	for (; ite != _vModeAdd.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite) == mode) { return true; }
	}
	return false;
}

// 登録IDから検索
ModeBase* ModeServer::Get(int uid) {
	// 登録中のもの、登録予約中のものから検索する
	lstModeBase::iterator ite;
	ite = _vMode.begin();
	for (; ite != _vMode.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_uid == uid) { return (*ite); }
	}
	ite = _vModeAdd.begin();
	for (; ite != _vModeAdd.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_uid == uid) { return (*ite); }
	}
	return NULL;
}

// 名前から検索
ModeBase* ModeServer::Get(const char* name) {
	// 登録中のもの、登録予約中のものから検索する
	lstModeBase::iterator ite;
	ite = _vMode.begin();
	for (; ite != _vMode.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_szName == name) { return (*ite); }
	}
	ite = _vModeAdd.begin();
	for (; ite != _vModeAdd.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_szName == name) { return (*ite); }
	}
	return NULL;
}

// ID取得
int ModeServer::GetId(ModeBase* mode) {
	if (IsAdd(mode)) {
		return mode->_uid;
	}
	return 0;
}
int ModeServer::GetId(const char* name) {
	return GetId(Get(name));
}

// 名前取得
const char* ModeServer::GetName(ModeBase* mode) {
	if (IsAdd(mode)) {
		return mode->_szName.c_str();
	}
	return NULL;
}
const char* ModeServer::GetName(int uid) {
	return GetName(Get(uid));
}




// プロセスを回すための初期化
int ModeServer::ProcessInit() {
	// 削除予約されていたものを削除
	if (_vModeDel.size() > 0) {
		lstModeBase::iterator ite = _vModeDel.begin();
		for (; ite != _vModeDel.end(); ++ite) {
			Release((*ite));
		}
		_vModeDel.clear();
	}
	// Add()されたものを有効にし、必要であればソートを行う
	if (_vModeAdd.size() > 0) {
		lstModeBase::iterator ite = _vModeAdd.begin();
		for (; ite != _vModeAdd.end(); ++ite) {
			(*ite)->Initialize(_game);
			_vMode.push_back((*ite));
		}
		_vModeAdd.clear();

		// レイヤーによるソートを行う
		_vMode.sort(modeSort);
	}

	// スキップ、ポーズの解除
	_skipProcessMode = NULL;
	_skipDrawMode = NULL;
	_pauseProcessMode = NULL;
	return 0;
}

int ModeServer::Process() {

	// 現在の時間を取得
	unsigned int t = GetNowCount();
	bool pause = false;

	// レイヤーの上の方から処理
	lstModeBase::reverse_iterator ite = _vMode.rbegin();
	for (; ite != _vMode.rend(); ++ite) {
		if (!IsDelRegist(*ite)) {
			_nowMode = (*ite);

			if (!pause) {
				// 時間経過処理
				(*ite)->StepTime(t);
			}

			// Processコール
			(*ite)->Process(_game);

			// Modeが無い場合 (Reboot時)
			if (_vMode.empty()) {
				break;
			}

			if (!pause) {
				// カウンタ処理
				(*ite)->StepCount();
			}
		}
		if (_skipProcessMode == (*ite)) { break; }
		if (_pauseProcessMode == (*ite)) { pause = true; }
	}
	_nowMode = NULL;

	return 0;
}

// プロセスを回した後の後始末
int ModeServer::ProcessFinish() {
	return 0;
}

// 描画を回すための初期化
int ModeServer::DrawInit() {
	ClearDrawScreen();		// 画面を初期化する
	return 0;
}

int ModeServer::Draw() {
	// レイヤーの下の方から処理
	lstModeBase::iterator ite = _vMode.begin();
	for (; ite != _vMode.end(); ++ite) {
		if (_skipDrawMode && _skipDrawMode != (*ite)) { continue; }
		_skipDrawMode = NULL;

		if (!IsDelRegist(*ite)) {
			_nowMode = (*ite);
			(*ite)->Draw(_game);
		}
	}
	_nowMode = NULL;
	return 0;
}

// 描画を回した後の後始末
int ModeServer::DrawFinish() {
	ScreenFlip();			// 裏画面の内容を表画面に反映させる
	return 0;
}



// 今処理しているレイヤーより下のレイヤーは、処理を呼ばない
int ModeServer::SkipProcessUnderLayer() {
	_skipProcessMode = _nowMode;
	return 0;
}

// 今処理しているレイヤーより下のレイヤーは、描画を呼ばない
int ModeServer::SkipDrawUnderLayer() {
	_skipDrawMode = _nowMode;
	return 0;
}


// 今処理しているレイヤーより下のレイヤーは、時間経過を止める
int ModeServer::PauseProcessUnderLayer() {
	_pauseProcessMode = _nowMode;
	return 0;
}