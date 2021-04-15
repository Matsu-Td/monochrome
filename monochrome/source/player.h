/** 
 * @file   player.h
 * @brief  �v���C���[�N���X
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "ObjectBase.h"
#include "Camera.h"

/**
 * @brief �v���C���[�N���X
 */
class Player : public ObjectBase {
public:
    Player(Game& g);
    ~Player();

    virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

    void Init(Game& g);
    void Process(Game& g);
    void Draw(Game& g);
    void Damage(Game& g);

    /**
     * �v���C���[��ԁA�ړ�������ύX����
     * @param g �Q�[���N���X�Q��
     * @param movx �ړ����X���W(�} or 0 �w��)
     * @param movz �ړ����Z���W(�} or 0 �w��)
     * @param stateAndDirection ��Ԃƈړ������w��
     */
    void MoveStateChange(Game& g, int movx, int movz, int stateAndDirection);

    /**
     * �v���C���[�ړ��A�A�j���[�V��������
     * @param moveX X���W�ړ�����(�} or 0 �w��)
     * @param moveZ Z���W�ړ�����(�} or 0 �w��)
     */
    void MoveMotion(int moveX, int moveZ);

private:
    static constexpr int MOVE_FLAME = 30;   // �ړ��t���[��
    static constexpr int ALPHA_MAX = 255;   // ���ő�l
    static constexpr int ALPHA_MIN = 0;     // ���ŏ��l
    static constexpr int GROUND_Y = 80;     // ���n�ʒu

    int _gameOverCnt;                // �Q�[���I�[�o�[�J�E���g
    int _moveTime;                   // �ړ�����
    int _state;                      // �ړ����
    int _g;                          // �d�͉����x
    int _alphaSwichCnt;              // �L���E���N���l�ؑ֗p�J�E���g                       
    int _delay;                      // �I�[�o�[�x���J�E���g�F�����[�����ڂł̃N���A���\�ɂ���
};
