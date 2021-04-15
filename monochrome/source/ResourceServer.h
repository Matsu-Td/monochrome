/** 
 * @file   ResourceServer.h
 * @brief  ���\�[�X�Ǘ��T�[�o�[
 * 
 * @author matsuo tadahiko
 * @date   2021/04/
 */

#pragma once

#include <unordered_map>

/**
 * @brief ���\�[�X�Ǘ��T�[�o�[�N���X
 */
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