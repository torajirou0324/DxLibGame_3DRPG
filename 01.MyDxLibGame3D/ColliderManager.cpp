//-----------------------------------------------------------------------------
// @brief  �Փ˔���Ǘ��N���X.
//-----------------------------------------------------------------------------
#include "ColliderManager.h"
#include <algorithm>

ColliderManager* ColliderManager::collisionManager = nullptr;

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
ColliderManager::ColliderManager()
{

}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
ColliderManager::~ColliderManager()
{
    m_boxColliderArray.clear();
    m_WallColliderArray.clear();
}

//-----------------------------------------------------------------------------
// @brief  ����.
//-----------------------------------------------------------------------------
void ColliderManager::CreateInstance()
{
    if (collisionManager == nullptr)
    {
        collisionManager = new ColliderManager;
    }
}

//-----------------------------------------------------------------------------
// @brief  ���.
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
// @brief  �Փ˔���ɕK�v�ȃI�u�W�F�N�g��ǉ�����.
//-----------------------------------------------------------------------------
void ColliderManager::AddColliderInfo(BoxCollider* _box)
{
    collisionManager->m_boxColliderArray.push_back(_box);
}

//-----------------------------------------------------------------------------
// @brief  �Փ˔���ɕK�v�ȃI�u�W�F�N�g��ǉ�����.
//-----------------------------------------------------------------------------
void ColliderManager::AddColliderInfo(WallCollider* _wall)
{
    collisionManager->m_WallColliderArray.push_back(_wall);
}

//-----------------------------------------------------------------------------
// @brief  �Փ˔���ɕK�v�Ȃ��I�u�W�F�N�g���폜����.
//-----------------------------------------------------------------------------
void ColliderManager::RemoveColliderInfo(BoxCollider* _box)
{
    // remove�͓���̗v�f�ȊO��L���̈�Ɉړ�������
    auto newend = std::remove(collisionManager->m_boxColliderArray.begin(), collisionManager->m_boxColliderArray.end(), _box);

    // �ړ������邾���ō폜�͂��Ȃ�����
    // �����̈���폜����ɂ�erase�ƕ��p���Ďg�p����
    collisionManager->m_boxColliderArray.erase(newend, collisionManager->m_boxColliderArray.end());
}

//-----------------------------------------------------------------------------
// @brief  �Փ˔���ɕK�v�Ȃ��I�u�W�F�N�g���폜����.
//-----------------------------------------------------------------------------
void ColliderManager::RemoveColliderInfo(WallCollider* _wall)
{
    // remove�͓���̗v�f�ȊO��L���̈�Ɉړ�������
    auto newend = std::remove(collisionManager->m_WallColliderArray.begin(), collisionManager->m_WallColliderArray.end(), _wall);

    // �ړ������邾���ō폜�͂��Ȃ�����
    // �����̈���폜����ɂ�erase�ƕ��p���Ďg�p����
    collisionManager->m_WallColliderArray.erase(newend, collisionManager->m_WallColliderArray.end());
}

//-----------------------------------------------------------------------------
// @brief  �Փ˔��������.
//-----------------------------------------------------------------------------
bool ColliderManager::OnCollisionEnter(ColliderBase* _coll)
{
    bool CollisionFlag = false;

    // �����蔻����s��������
    if (_coll->GetOnCollisionFlag())
    {
        for (int i = 0; i < collisionManager->m_WallColliderArray.size(); i++)
        {
            if (_coll == collisionManager->m_WallColliderArray[i] || !collisionManager->m_WallColliderArray[i]->GetOnCollisionFlag())
            {
                continue;
            }

            // �����ȊO�̃R���C�_�[�Ɠ������Ă�����
            if (_coll->HitCheck(collisionManager->m_WallColliderArray[i]))
            {
                // ���������Ƃ��̏������s��
                CollisionFlag = true;
            }
        }

        // �ǗD��
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

            // �����ȊO�̃R���C�_�[�Ɠ������Ă�����
            if (_coll->HitCheck(collisionManager->m_boxColliderArray[i]))
            {
                // ���������Ƃ��̏������s��
                CollisionFlag = true;
            }
        }
    }
    return CollisionFlag;
}

// �{�b�N�X�̕`��
void CollDraw3D(VECTOR st, VECTOR en, unsigned int color)
{
    DrawLine3D(VGet(st.x, st.y, en.z), VGet(en.x, st.y, en.z), color);	// ���̉�
    DrawLine3D(VGet(st.x, en.y, en.z), en, color);						// ��̉�
    DrawLine3D(VGet(st.x, st.y, en.z), VGet(st.x, en.y, en.z), color);	// ���̏c
    DrawLine3D(VGet(en.x, st.y, en.z), en, color);						// �E�̏c

    DrawLine3D(st, VGet(en.x, st.y, st.z), color);	                    // ���̉�
    DrawLine3D(VGet(st.x, en.y, st.z), VGet(en.x, en.y, st.z), color);	// ��̉�
    DrawLine3D(st, VGet(st.x, en.y, st.z), color);	                    // ���̏c
    DrawLine3D(VGet(en.x, st.y, st.z), VGet(en.x, en.y, st.z), color);	// �E�̏c

    DrawLine3D(st, VGet(st.x, st.y, en.z), color);                      // 
    DrawLine3D(VGet(st.x, en.y, st.z), VGet(st.x, en.y, en.z), color);  // 
    DrawLine3D(VGet(en.x, st.y, st.z), VGet(en.x, st.y, en.z), color);  // 
    DrawLine3D(VGet(en.x, en.y, st.z), en, color);                      // 
}

// �ǂ̕`��
void CollDraw3D(VECTOR st, VECTOR en, float he, unsigned int color)
{
    DrawLine3D(st, en, color);                                                      // ���̉�
    DrawLine3D(VGet(st.x, st.y + he, st.z), VGet(en.x, en.y + he, en.z), color);    // ��̉�
    DrawLine3D(st, VGet(st.x, st.y + he, st.z), color);                             // ���̏c
    DrawLine3D(en, VGet(en.x, en.y + he, en.z), color);                             // �E�̏c
}

void ColliderManager::ColliderVisuale()
{
    auto color = GetColor(0, 255, 0);

    // �{�b�N�X�`��
    for (int i = 0; i < collisionManager->m_boxColliderArray.size(); i++)
    {
        VECTOR start = collisionManager->m_boxColliderArray[i]->GetBoxAddress()->m_min;
        VECTOR end = collisionManager->m_boxColliderArray[i]->GetBoxAddress()->m_max;
        CollDraw3D(start, end, color);
    }
    // �Ǖ`��
    for (int i = 0; i < collisionManager->m_WallColliderArray.size(); i++)
    {
        VECTOR start = collisionManager->m_WallColliderArray[i]->GetWallAdress()->m_start;
        VECTOR end = collisionManager->m_WallColliderArray[i]->GetWallAdress()->m_end;
        float height = collisionManager->m_WallColliderArray[i]->GetWallAdress()->m_height;
        CollDraw3D(start, end, height, color);
    }
}
