//-----------------------------------------------------------------------------
// @brief  プレイヤーとエネミーの基底クラス.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <DxLib.h>
#include "AssetManager.h"
#include "Status.h"
#include "Skill.h"

// アニメーション管理列挙体
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
        , m_isDeathFlag(false)
        , m_enActionFlag(false)
        , m_attackNow(false)
        , m_name("")
        , m_position(VGet(0.0f,0.0f,0.0f))
        , m_status()
        , m_basicStatus()
        , m_animType(Idle)
        , m_beforeAnimType(Idle)
        , m_pAttackObject(nullptr)
    {
        // アニメーションを保存
        m_animHandle[0] = AssetManager::UseModel(AssetManager::AnimIdle);
        m_animHandle[1] = AssetManager::UseModel(AssetManager::AnimWalk);
        m_animHandle[2] = AssetManager::UseModel(AssetManager::AnimAttack);
        m_animHandle[3] = AssetManager::UseModel(AssetManager::AnimDamage);
        m_animHandle[4] = AssetManager::UseModel(AssetManager::AnimDeath);
    }
    virtual ~Character(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;

    virtual void Move() = 0;

    void Attack()           // エネミーからプレイヤーへ攻撃用処理
    {
        int ATK = 0;
        if (m_useSkill.SkillType == AttributeType::Physical)
        {
            ATK = m_status.ATK + m_useSkill.Power;
            ATK = static_cast<int>(ATK / 2) - static_cast<int>(m_pAttackObject->GetAllStatus().DEF / 4);
        }
        if (m_useSkill.SkillType == AttributeType::Special)
        {
            ATK = m_status.INT + m_useSkill.Power;
            ATK = static_cast<int>(ATK / 2) - static_cast<int>(m_pAttackObject->GetAllStatus().RES / 4);
        }

        m_status.MP = m_status.MP - m_useSkill.MagicPower;
        m_animType = Anim::Attack;  // 攻撃アニメーション開始
        m_attackNow = true;
        m_pAttackObject->Damage(ATK);
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

        m_animType = Anim::Damage;  // 被ダメアニメーション開始
    }

    void Heal()
    {
        int HP = m_status.HP;
        HP = HP + m_useSkill.Power;
        if (HP > m_hpMax)
        {
            HP = m_hpMax;
        }
    }

    void Dead()             // 死ぬときに呼ぶ(両対応)
    {
        m_animType = Anim::Death;
    }

    void ActionInit()       // 行動可能に
    {
        m_enActionFlag = false;
    }

    void Action()           // 行動済に
    {
        m_enActionFlag = true;
    }

    // セッター
    void SetAttackObjectAddress(Character* _AttackObject) { m_pAttackObject = _AttackObject; }

    // ゲッター
    const bool &GetDeathFlag()          // 死んでいるかどうか
    {
        return m_isDeathFlag;
    }
    const bool &GetActionFlag()         // 行動したか
    {
        return m_enActionFlag;
    }
    const bool& GetAttackNowFlag()      // 攻撃中かどうか
    {
        return m_attackNow;
    }
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_status; }
    const int& GetHPMAX() const { return m_hpMax; }
    const bool& GetDiscrimination() const { return m_isPlayerFlag; }
protected:

    int m_animHandle[5];	    // アニメーションのモデルハンドル.
    int m_modelHandle;          // キャラクター自身のモデルハンドル
    int m_hpMax;                // キャラクターの最大HP保存用

    float m_animTime;           // アニメーションの経過時間
    float m_animTotalTime;      // アニメーションの総再生時間

    bool m_isPlayerFlag;        // プレイヤーかどうか
    bool m_isDeathFlag;         // 死んだかどうか
    bool m_enActionFlag;        // 行動が終わったか
    bool m_attackNow;           // 攻撃中かどうか

    std::string m_name;         // キャラクターの名前
    VECTOR m_position;          // キャラクターの座標

    Status m_status;            // キャラクターのステータス（戦闘時変化用）
    Status m_basicStatus;       // キャラクターステータス（基礎ステータス）
    SKILL m_skillStorage[3];    // 技格納用の配列
    SKILL m_useSkill;		    // 使用する技格納用.

    Anim m_animType;            // 現在のアニメーション保存用
    Anim m_beforeAnimType;      // 1つ前のアニメーション保存用

    Character* m_pAttackObject; // 攻撃する相手格納用変数
};