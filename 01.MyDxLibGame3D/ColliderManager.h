//-----------------------------------------------------------------------------
// @brief  �Փ˔���Ǘ��N���X.
//-----------------------------------------------------------------------------

#pragma once
#include <vector>
#include "BoxCollider.h"
#include "WallCollider.h"

class ColliderManager
{
    // �V���O���g��
    static ColliderManager* collisionManager;
    // �S�ẴR���C�_�[�i�[�z��
    std::vector<BoxCollider*> m_boxColliderArray;
    std::vector<WallCollider*> m_WallColliderArray;

public:
    // �R�s�[�֎~
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;

    ColliderManager();
    ~ColliderManager();

    static void CreateInstance();
    static void DeleteInstance();

    // �ǉ�
    static void AddColliderInfo(BoxCollider* _box);
    static void AddColliderInfo(WallCollider* _wall);
    // �폜
    static void RemoveColliderInfo(BoxCollider* _box);
    static void RemoveColliderInfo(WallCollider* _wall);
    // �Փ˔���
    static bool OnCollisionEnter(ColliderBase* _coll);
    // ������R���C�_�[����������
    static void ColliderVisuale();
};