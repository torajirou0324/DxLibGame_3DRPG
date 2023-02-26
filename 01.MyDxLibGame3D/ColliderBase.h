//-----------------------------------------------------------------------------
// @brief  コライダーの基底クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Collision.h"

// オブジェクトタグ
enum class ObjectTag
{
    Player,     // 自分
    Enemy,      // 敵
    Wall,       // 壁
    Ground,     // 地面
    None
};

class ColliderBase
{
public:
    ColliderBase()              // コンストラクタ
        : m_pCollInfo(nullptr)
        , m_onCollisionTag(ObjectTag::None)
        , m_onCollisionFlag(false)
    {}
    virtual ~ColliderBase(){}   // デストラクタ(継承先でオーバーライド用)

    // 当たり判定を実行するかしないかのフラグを返す
    const bool& GetOnCollisionFlag() { return m_onCollisionFlag; }

    // 当たり判定を検出(相手のコライダー)
    // 当たり判定結果を返す
    virtual bool HitCheck(class BoxCollider* _other) { return false; }
    virtual bool HitCheck(class WallCollider* _other) { return false; }

    // 当たり判定情報を返す
    CollisionInfo& GetCollisionInfo() { return *m_pCollInfo; }
protected:
    CollisionInfo* m_pCollInfo;     // 当たり判定情報
    ObjectTag m_onCollisionTag;     // 当たったオブジェクトのタグ名

    bool m_onCollisionFlag;         // 当たり判定を行うかどうか
};