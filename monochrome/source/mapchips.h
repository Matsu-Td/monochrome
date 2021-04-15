/** 
 * @file   mapchips.h
 * @brief  マップデータ、JSONファイル読み込み
 * 
 * @author matsuo tadahiko
 */

#pragma once

class Game;

#include <string>

/**
 * @brief マップデータ、JSONファイル読み込み
 */
class MapChips {
public:
	MapChips(std::string filePath, std::string tiledFileName);
	~MapChips();

	void Draw(Game& g);

public:
    int _mapSizeX;     // マップのサイズ(width)
    int _mapSizeZ;     // マップのサイズ(height)

    int _blockSizeX;   // ブロックサイズX
    int _blockSizeZ;   // ブロックサイズZ

    int _mapSizeLayer; // レイヤー数

    std::string	_strChipFile;  // チップデータのファイル名

    int* _mapData;     // マップデータ

private:
    std::string StringFileLoad(std::string strFileName);
    int	TiledJsonLoad(std::string filePath, std::string strFileName);

	int _mh[2];    // 3Dモデルハンドル(ステージ用)
};