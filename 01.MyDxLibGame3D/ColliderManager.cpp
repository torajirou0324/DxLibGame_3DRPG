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
    m_boxColliderArray.clear();
    m_WallColliderArray.clear();
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
void ColliderManager::AddColliderInfo(BoxCollider* _box)
{
    collisionManager->m_boxColliderArray.push_back(_box);
}

//-----------------------------------------------------------------------------
// @brief  衝突判定に必要なオブジェクトを追加する.
//-----------------------------------------------------------------------------
void ColliderManager::AddColliderInfo(WallCollider* _wall)
{
    collisionManager->m_WallColliderArray.push_back(_wall);
}

//-----------------------------------------------------------------------------
// @brief  衝突判定に必要ないオブジェクトを削除する.
//-----------------------------------------------------------------------------
void ColliderManager::RemoveColliderInfo(BoxCollider* _box)
{
    // removeは特定の要素以外を有効領域に移動させる
    auto newend = std::remove(collisionManager->m_boxColliderArray.begin(), collisionManager->m_boxColliderArray.end(), _box);

    // 移動させるだけで削除はしないため
    // 無効領域を削除するにはeraseと併用して使用する
    collisionManager->m_boxColliderArray.erase(newend, collisionManager->m_boxColliderArray.end());
}

//-----------------------------------------------------------------------------
// @brief  衝突判定に必要ないオブジェクトを削除する.
//-----------------------------------------------------------------------------
void ColliderManager::RemoveColliderInfo(WallCollider* _wall)
{
    // removeは特定の要素以外を有効領域に移動させる
    auto newend = std::remove(collisionManager->m_WallColliderArray.begin(), collisionManager->m_WallColliderArray.end(), _wall);

    // 移動させるだけで削除はしないため
    // 無効領域を削除するにはeraseと併用して使用する
    collisionManager->m_WallColliderArray.erase(newend, collisionManager->m_WallColliderArray.end());
}

//-----------------------------------------------------------------------------
// @brief  衝突判定をする.
//-----------------------------------------------------------------------------
bool ColliderManager::OnCollisionEnter(ColliderBase* _coll)
{
    bool CollisionFlag = false;

    // 当たり判定を行うか判定
    if (_coll->GetOnCollisionFlag())
    {
        for (int i = 0; i < collisionManager->m_WallColliderArray.size(); i++)
        {
            if (_coll == collisionManager->m_WallColliderArray[i] || !collisionManager->m_WallColliderArray[i]->GetOnCollisionFlag())
            {
                continue;
            }

            // 自分以外のコライダーと当たっていたら
            if (_coll->HitCheck(collisionManager->m_WallColliderArray[i]))
            {
                // 当たったときの処理を行う
                CollisionFlag = true;
            }
        }

        // 壁優先
        if (CollisionFlag)
        {
            return CollisionFlag = true;
        }

        for (int i = 0; i < collisionManager->m_boxColliderArray.size(); i++)
        {
            if (_coll == collisionManager->m_boxColliderArray[i] || !collisionManager->m_boxColliderArray[i]->GetOnCollisionFlag())
            {
                continue;
            }

            // 自分以外のコライダーと当たっていたら
            if (_coll->HitCheck(collisionManager->m_boxColliderArray[i]))
            {
                // 当たったときの処理を行う
                CollisionFlag = true;
            }
        }
    }
    return CollisionFlag;
}

// ボックスの描画
void CollDraw3D(VECTOR st, VECTOR en, unsigned int color)
{
    DrawLine3D(VGet(st.x, st.y, en.z), VGet(en.x, st.y, en.z), color);	// 下の横
    DrawLine3D(VGet(st.x, en.y, en.z), en, color);						// 上の横
    DrawLine3D(VGet(st.x, st.y, en.z), VGet(st.x, en.y, en.z), color);	// 左の縦
    DrawLine3D(VGet(en.x, st.y, en.z), en, color);						// 右の縦

    DrawLine3D(st, VGet(en.x, st.y, st.z), color);	                    // 下の横
    DrawLine3D(VGet(st.x, en.y, st.z), VGet(en.x, en.y, st.z), color);	// 上の横
    DrawLine3D(st, VGet(st.x, en.y, st.z), color);	                    // 左の縦
    DrawLine3D(VGet(en.x, st.y, st.z), VGet(en.x, en.y, st.z), color);	// 右の縦

    DrawLine3D(st, VGet(st.x, st.y, en.z), color);                      // 
    DrawLine3D(VGet(st.x, en.y, st.z), VGet(st.x, en.y, en.z), color);  // 
    DrawLine3D(VGet(en.x, st.y, st.z), VGet(en.x, st.y, en.z), color);  // 
    DrawLine3D(VGet(en.x, en.y, st.z), en, color);                      // 
}

// 壁の描画
void CollDraw3D(VECTOR st, VECTOR en, float he, unsigned int color)
{
    DrawLine3D(st, en, color);                                                      // 下の横
    DrawLine3D(VGet(st.x, st.y + he, st.z), VGet(en.x, en.y + he, en.z), color);    // 上の横
    DrawLine3D(st, VGet(st.x, st.y + he, st.z), color);                             // 左の縦
    DrawLine3D(en, VGet(en.x, en.y + he, en.z), color);                             // 右の縦
}

void ColliderManager::ColliderVisuale()
{
    auto color = GetColor(0, 255, 0);

    // ボックス描画
    for (int i = 0; i < collisionManager->m_boxColliderArray.size(); i++)
    {
        VECTOR start = collisionManager->m_boxColliderArray[i]->GetBoxAddress()->m_min;
        VECTOR end = collisionManager->m_boxColliderArray[i]->GetBoxAddress()->m_max;
        CollDraw3D(start, end, color);
    }
    // 壁描画
    for (int i = 0; i < collisionManager->m_WallColliderArray.size(); i++)
    {
        VECTOR start = collisionManager->m_WallColliderArray[i]->GetWallAdress()->m_start;
        VECTOR end = collisionManager->m_WallColliderArray[i]->GetWallAdress()->m_end;
        float height = collisionManager->m_WallColliderArray[i]->GetWallAdress()->m_height;
        CollDraw3D(start, end, height, color);
    }
}
