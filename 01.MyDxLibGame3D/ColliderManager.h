//-----------------------------------------------------------------------------
// @brief  衝突判定管理クラス.
//-----------------------------------------------------------------------------

#pragma once
#include <vector>
#include "ColliderBase.h"

class ColliderManager
{
    // シングルトン
    static ColliderManager* collisionManager;
    // 全てのコライダー格納配列
    std::vector<ColliderBase*> m_colliderArray;

public:
    // コピー禁止
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    ColliderManager();
    ~ColliderManager();

    static void CreateInstance();
    static void DeleteInstance();

    static void AddColliderInfo(ColliderBase* _coll);
    static void RemoveColliderInfo(ColliderBase* _coll);
    static bool OnCollisionEnter(ColliderBase* _coll);
};