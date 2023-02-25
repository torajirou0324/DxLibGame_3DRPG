//-----------------------------------------------------------------------------
// @brief  �Փ˔���Ǘ��N���X.
//-----------------------------------------------------------------------------

#pragma once
#include <vector>
#include "ColliderBase.h"

class ColliderManager
{
    // �V���O���g��
    static ColliderManager* collisionManager;
    // �S�ẴR���C�_�[�i�[�z��
    std::vector<ColliderBase*> m_colliderArray;

public:
    // �R�s�[�֎~
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