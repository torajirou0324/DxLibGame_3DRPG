//-----------------------------------------------------------------------------
// @brief  衝突判定管理クラス.
//-----------------------------------------------------------------------------
#include "ColliderManager.h"
#include <algorithm>

ColliderManager* ColliderManager::collisionManager = nullptr;

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
ColliderManager::ColliderManager()
{

}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
ColliderManager::~ColliderManager()
{
}

//-----------------------------------------------------------------------------
// @brief  生成.
//-----------------------------------------------------------------------------
void ColliderManager::CreateInstance()
{
    if (collisionManager == nullptr)
    {
        collisionManager = new ColliderManager;
    }
}

//-----------------------------------------------------------------------------
// @brief  解放.
//-----------------------------------------------------------------------------
void ColliderManager::DeleteInstance()
{
    if (collisionManager != nullptr)
    {
        delete collisionManager;
        collisionManager = nullptr;
    }
}

//-----------------------------------------------------------------------------
// @brief  衝突判定に必要なオブジェクトを追加する.
//-----------------------------------------------------------------------------
void ColliderManager::AddColliderInfo(ColliderBase* _coll)
{
    collisionManager->m_colliderArray.push_back(_coll);
}

//-----------------------------------------------------------------------------
// @brief  衝突判定に必要ないオブジェクトを削除する.
//-----------------------------------------------------------------------------
void ColliderManager::RemoveColliderInfo(ColliderBase* _coll)
{
    // removeは特定の要素以外を有効領域に移動させる
    auto newend = std::remove(collisionManager->m_colliderArray.begin(), collisionManager->m_colliderArray.end(), _coll);

    // 移動させるだけで削除はしないため
    // 無効領域を削除するにはeraseと併用して使用する
    collisionManager->m_colliderArray.erase(newend, collisionManager->m_colliderArray.end());
}

//-----------------------------------------------------------------------------
// @brief  衝突判定をする.
//-----------------------------------------------------------------------------
bool ColliderManager::OnCollisionEnter(ColliderBase* _coll)
{
}
