//-----------------------------------------------------------------------------
// @brief  �R���C�_�[�̊��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Collision.h"

// �I�u�W�F�N�g�^�O
enum class ObjectTag
{
    Player,     // ����
    Enemy,      // �G
    Wall,       // ��
    Ground,     // �n��
    None
};

class ColliderBase
{
public:
    ColliderBase()              // �R���X�g���N�^
        : m_pCollInfo(nullptr)
        , m_onCollisionTag(ObjectTag::None)
        , m_onCollisionFlag(false)
    {}
    virtual ~ColliderBase(){}   // �f�X�g���N�^(�p����ŃI�[�o�[���C�h�p)

    // �����蔻������s���邩���Ȃ����̃t���O��Ԃ�
    const bool& GetOnCollisionFlag() { return m_onCollisionFlag; }
    void SetOnCollisionFlag(bool _flag) { m_onCollisionFlag = _flag; }
    const ObjectTag& GetOnCollisionTag() { return m_onCollisionTag; }

    void CollisionInit() { m_onCollisionTag = ObjectTag::None; }
    // �����蔻������o(����̃R���C�_�[)
    // �����蔻�茋�ʂ�Ԃ�
    virtual bool HitCheck(class BoxCollider* _other) { return false; }
    virtual bool HitCheck(class WallCollider* _other) { return false; }

    // �����蔻�����Ԃ�
    CollisionInfo& GetCollisionInfo() { return *m_pCollInfo; }
protected:
    CollisionInfo* m_pCollInfo;     // �����蔻����
    ObjectTag m_onCollisionTag;     // ���������I�u�W�F�N�g�̃^�O��
    ObjectTag m_ownTag;
    bool m_onCollisionFlag;         // �����蔻����s�����ǂ���
};