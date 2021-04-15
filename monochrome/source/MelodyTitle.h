/** 
 * @file   MelodyTitle.h
 * @brief  �^�C�g����ʊl�������\��
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "game.h"

/**
 * @brief �^�C�g����ʊl�������\��
 */
class MelodyTitle{
public:
	MelodyTitle();

	void Init();
	void Process(Game& g);
	void Draw(Game& g);

private:
	static constexpr float ALPHA_MAX = 255.0f;   // ���ő�l
	static constexpr float ALPHA_MIN = 0.0f;     // ���ŏ��l
	static constexpr int MELODY_ALL = 6;         // �����f�B�̂����瑍��
	const int X[MELODY_ALL] = { 250,350,450,550,640,700 };   // �����f�B�̂�����X���W
	const int Y[MELODY_ALL] = { 100,122,145,148,115,60 };    // �����f�B�̂�����Y���W
	const float ROT[MELODY_ALL] = { 20.0f,20.0f,18.0f,0.0f,-20.0f,-45.0f };  // �����f�B�̂������]�l

	int _cgMelody[2];     // �����f�B�̂�����
	int _cgGosenhu;       // �ܐ���

	int _w[2];            // �摜�T�C�Y(����)
	int _h;               // �摜�T�C�Y(�c��)
	float _melodyAlpha;   // �����f�B�̂����烿�u�����h
	int _alphaSwitch;     // �����f�B�̂����烿�u�����h�����ؑ�
};