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
        , m_isDeath(false)
        , m_name("")
        , m_position(VGet(0.0f,0.0f,0.0f))
        , m_status()
        , m_animType(Idle)
        , m_beforeAnimType(Idle)
    {}
    virtual ~Character(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;

    void Attack()           // エネミーからプレイヤーへ攻撃用処理
    {
        Player::Damage(m_status.ATK);
    }

    void Damage(int atk)    // 被ダメ処理（両対応）
    {
        int HP = m_status.HP;
        HP = HP - atk;
        if (HP < 0)
        {
            HP = 0;
        }
        m_status.HP = HP;
    }

    bool GetDeathFlag()     // 死んでいるかどうか
    {
        return m_isDeath;
    }

    // ゲッター
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_status; }
    const int& GetHPMAX() { return m_hpMax; }
protected:
    int m_modelHandle;      // キャラクター自身のモデルハンドル
    int m_hpMax;            // キャラクターの最大HP保存用

    float m_animTime;       // アニメーションの経過時間
    float m_animTotalTime;  // アニメーションの総再生時間

    bool m_isDeath;         // 死んだかどうか

    std::string m_name;     // キャラクターの名前
    VECTOR m_position;      // キャラクターの座標
    Status m_status;        // キャラクターのステータス

    Anim m_animType;        // 現在のアニメーション保存用
    Anim m_beforeAnimType;  // 1つ前のアニメーション保存用
};