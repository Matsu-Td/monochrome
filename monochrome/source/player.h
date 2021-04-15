/** 
 * @file   player.h
 * @brief  プレイヤークラス
 * 
 * @author matsuo tadahiko
 */

#pragma once

#include "ObjectBase.h"
#include "Camera.h"

/**
 * @brief プレイヤークラス
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
     * プレイヤー状態、移動方向を変更する
     * @param g ゲームクラス参照
     * @param movx 移動先のX座標(± or 0 指定)
     * @param movz 移動先のZ座標(± or 0 指定)
     * @param stateAndDirection 状態と移動方向指定
     */
    void MoveStateChange(Game& g, int movx, int movz, int stateAndDirection);

    /**
     * プレイヤー移動、アニメーション処理
     * @param moveX X座標移動方向(± or 0 指定)
     * @param moveZ Z座標移動方向(± or 0 指定)
     */
    void MoveMotion(int moveX, int moveZ);

private:
    static constexpr int MOVE_FLAME = 30;   // 移動フレーム
    static constexpr int ALPHA_MAX = 255;   // α最大値
    static constexpr int ALPHA_MIN = 0;     // α最小値
    static constexpr int GROUND_Y = 80;     // 着地位置

    int _gameOverCnt;                // ゲームオーバーカウント
    int _moveTime;                   // 移動時間
    int _state;                      // 移動状態
    int _g;                          // 重力加速度
    int _alphaSwichCnt;              // キュウリ君α値切替用カウント                       
    int _delay;                      // オーバー遅延カウント：歩数ゼロ歩目でのクリアを可能にする
};
