//-----------------------------------------------------------------------------
// @brief  マップを徘徊する敵クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Character.h"
#include "BoxCollider.h"

class WalkAroundEnemy
{
public:
    WalkAroundEnemy();
    ~WalkAroundEnemy();

    void Init(const VECTOR& _pos, int _ownLevel, int _otherLevel);
    void Update();
    void Draw();
    void Animation();		// アニメーション処理.

    // ゲッター
    // レベル
    const int& GetLevel() { return m_level; }
    // 出す敵の総数
    const int& GetEnemyNum() { return m_num; }

    // プレイヤーと当たっているかのフラグ
    const bool& GetIsCollisionPlayerFlag() { return m_isCollisionPlayer; }
private:
    // めり込みの押し戻し量を加える(当たり判定)
    void PushbackVolume();

    void Move();
    void Rotate();
    // 二つのベクトルの角度が同じか.
    bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
    // nowVecからdirVecの最短の回転方向を調べる(Y軸).
    float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
    // nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する.
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

    int m_animHandle[5];	    // アニメーションのモデルハンドル.
    int m_modelHandle;          // キャラクター自身のモデルハンドル.
    int m_iconHandle;           // 頭の上のアイコンのモデルハンドル.
    int m_level;                // 生成するための最大レベル値.
    int m_num;                  // 生成するための敵の最大数(3体まで).

    int m_timer;

    float m_animTime;           // アニメーションの経過時間.
    float m_animTotalTime;      // アニメーションの総再生時間.

    bool m_rotateNow;		    // 回転中か判定用.
    bool m_isCollisionPlayer;   // プレイヤーと当たったか.

    VECTOR m_position;      // 座標.
    VECTOR m_rotate;		// 角度.
    VECTOR m_velocity;		// 速度.
    VECTOR m_dir;			// 向き.
    VECTOR m_aimDir;		// 目標方向.

    BoxCollider* m_pBoxCollider;

    Anim m_animType;            // 現在のアニメーション保存用.
    Anim m_beforeAnimType;      // 1つ前のアニメーション保存用.
};