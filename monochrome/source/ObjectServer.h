#pragma once

/**
 * @file ObjectServer.h
 * @brief オブジェクト管理サーバークラス
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include <vector>
#include "ObjectBase.h"

class Game;

class ObjectServer {
public:
	ObjectServer();
	~ObjectServer();

	void Clear();
	void Add(ObjectBase* obj);
	void Del(ObjectBase* obj);

	void Process(Game& g);
	void Draw(Game& g);

	std::vector<ObjectBase*>* List() { return &_vObject; }

private:
	void AddListObjects();
	void DelListObjects();

protected:
	std::vector<ObjectBase*> _vObject; // ObjectBaseを登録するリスト
	std::vector<ObjectBase*> _vAdd;    // 追加するオブジェクトリスト
	std::vector<ObjectBase*> _vDel;	   // 削除するオブジェクトリスト
};