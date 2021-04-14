#pragma once

/**
 * @file ResourceServer.h
 * @brief ���\�[�X�Ǘ��T�[�o�[
 *
 * @date 2020-07-16
 * @author �������F
 */

#include <unordered_map>

class ResourceServer {
public:
	static void Init();
	static void Release();

	static void ClearGraph();
	static int LoadGraph(const TCHAR* FileName);
	static int LoadSoundMem(const TCHAR* FileName);
	static int LoadDivGraph(const TCHAR* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleBuf);

private:
	static std::unordered_map<std::string, int> _mapGraph;
	
	typedef struct {
		int	AllNum;
		int* handle;
	} DIVGRAPH;
	static std::unordered_map<std::string, DIVGRAPH> _mapDivGraph;

	static std::unordered_map<std::string, int>	_mapSound;
	static std::unordered_map<std::string, int>	_mapModel;
};