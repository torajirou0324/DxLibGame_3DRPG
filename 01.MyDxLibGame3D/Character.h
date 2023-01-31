//-----------------------------------------------------------------------------
// @brief  プレイヤーとエネミーの基底クラス.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <DxLib.h>
#include "Status.h"

// アニメーション管理構造体
enum Anim
{
    Idle,               // 待機
    Walk,               // 歩き
    Attack,             // 攻撃
    Damage,             // 被ダメ
    Death               // 死亡
};

class Character
{
public:
    Character()
        : m_modelHandle(-1)
        , m_hpMax(0)
        , m_animTime(0.0f)
        , m_animTotalTime(0.0f)
        , m_name("")
        , m_position(VGet(0.0f,0.0f,0.0f))
        , m_status()
        , m_animType(Idle)
        , m_beforeAnimType(Idle)
    {}
    virtual ~Character(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    int m_modelHandle;      // キャラクター自身のモデルハンドル
    int m_hpMax;            // キャラクターの最大HP保存用

    float m_animTime;       // アニメーションの経過時間
    float m_animTotalTime;  // アニメーションの総再生時間

    std::string m_name;     // キャラクターの名前
    VECTOR m_position;      // キャラクターの座標
    Status m_status;        // キャラクターのステータス

    Anim m_animType;        // 現在のアニメーション保存用
    Anim m_beforeAnimType;  // 1つ前のアニメーション保存用
};