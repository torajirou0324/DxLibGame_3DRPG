//-----------------------------------------------------------------------------
// @brief  衝突判定管理クラス.
//-----------------------------------------------------------------------------

#pragma once
#include <vector>
#include "BoxCollider.h"
#include "WallCollider.h"

class ColliderManager
{
    // シングルトン
    static ColliderManager* collisionManager;
    // 全てのコライダー格納配列
    std::vector<BoxCollider*> m_boxColliderArray;
    std::vector<WallCollider*> m_WallColliderArray;

public:
    // コピー禁止
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    ColliderManager();
    ~ColliderManager();

    static void CreateInstance();
    static void DeleteInstance();

    // 追加
    static void AddColliderInfo(BoxCollider* _box);
    static void AddColliderInfo(WallCollider* _wall);
    // 削除
    static void RemoveColliderInfo(BoxCollider* _box);
    static void RemoveColliderInfo(WallCollider* _wall);
    // 衝突判定
    static bool OnCollisionEnter(ColliderBase* _coll);
    // 今あるコライダーを可視化する
    static void ColliderVisuale();
};