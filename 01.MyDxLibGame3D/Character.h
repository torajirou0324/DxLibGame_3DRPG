//-----------------------------------------------------------------------------
// @brief  プレイヤーとエネミーの基底クラス.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <DxLib.h>
#include "AssetManager.h"
#include "Status.h"

// プレイヤーか敵かを判定する用列挙体
enum CharacterName
{
    Human,      // 人（プレイヤー）
    UnHuman,    // 人外（敵）
};

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
        , m_name("")
        , m_position(VGet(0.0f,0.0f,0.0f))
        , m_status()
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

    void Attack()           // エネミーからプレイヤーへ攻撃用処理
    {
        int ATK = m_status.ATK;
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
    }

    void Dead()             // 死ぬときに呼ぶ(両対応)
    {
        m_isDeathFlag = true;
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
    const bool GetDeathFlag()       // 死んでいるかどうか
    {
        return m_isDeathFlag;
    }
    const bool GetActionFlag()      // 行動したか
    {
        return m_enActionFlag;
    }
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_status; }
    const CharacterName& GetCharaName() const { return m_CharaName; }
    const int& GetHPMAX() { return m_hpMax; }
protected:
    int m_animHandle[5];	    // アニメーションのモデルハンドル.
    int m_modelHandle;          // キャラクター自身のモデルハンドル
    int m_hpMax;                // キャラクターの最大HP保存用

    float m_animTime;           // アニメーションの経過時間
    float m_animTotalTime;      // アニメーションの総再生時間

    bool m_isDeathFlag;         // 死んだかどうか
    bool m_enActionFlag;        // 行動が終わったか

    std::string m_name;         // キャラクターの名前
    VECTOR m_position;          // キャラクターの座標
    Status m_status;            // キャラクターのステータス

    Anim m_animType;            // 現在のアニメーション保存用
    Anim m_beforeAnimType;      // 1つ前のアニメーション保存用

    CharacterName m_CharaName;  // キャラクターが人か人外か判定用
private:
    Character* m_pAttackObject; // 攻撃する相手格納用変数
};