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
void ColliderManager::AddColliderInfo(ColliderBase* _coll)
{
    collisionManager->m_colliderArray.push_back(_coll);
}

//-----------------------------------------------------------------------------
// @brief  �Փ˔���ɕK�v�Ȃ��I�u�W�F�N�g���폜����.
//-----------------------------------------------------------------------------
void ColliderManager::RemoveColliderInfo(ColliderBase* _coll)
{
    // remove�͓���̗v�f�ȊO��L���̈�Ɉړ�������
    auto newend = std::remove(collisionManager->m_colliderArray.begin(), collisionManager->m_colliderArray.end(), _coll);

    // �ړ������邾���ō폜�͂��Ȃ�����
    // �����̈���폜����ɂ�erase�ƕ��p���Ďg�p����
    collisionManager->m_colliderArray.erase(newend, collisionManager->m_colliderArray.end());
}

//-----------------------------------------------------------------------------
// @brief  �Փ˔��������.
//-----------------------------------------------------------------------------
bool ColliderManager::OnCollisionEnter(ColliderBase* _coll)
{
}
