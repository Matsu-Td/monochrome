/** 
 * @file   mapchips.h
 * @brief  �}�b�v�f�[�^�AJSON�t�@�C���ǂݍ���
 * 
 * @author matsuo tadahiko
 */

#pragma once

class Game;

#include <string>

/**
 * @brief �}�b�v�f�[�^�AJSON�t�@�C���ǂݍ���
 */
class MapChips {
public:
	MapChips(std::string filePath, std::string tiledFileName);
	~MapChips();

	void Draw(Game& g);

public:
    int _mapSizeX;     // �}�b�v�̃T�C�Y(width)
    int _mapSizeZ;     // �}�b�v�̃T�C�Y(height)

    int _blockSizeX;   // �u���b�N�T�C�YX
    int _blockSizeZ;   // �u���b�N�T�C�YZ

    int _mapSizeLayer; // ���C���[��

    std::string	_strChipFile;  // �`�b�v�f�[�^�̃t�@�C����

    int* _mapData;     // �}�b�v�f�[�^

private:
    std::string StringFileLoad(std::string strFileName);
    int	TiledJsonLoad(std::string filePath, std::string strFileName);

	int _mh[2];    // 3D���f���n���h��(�X�e�[�W�p)
};