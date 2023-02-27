//-----------------------------------------------------------------------------
// @brief  �{�b�N�X�̓����蔻��N���X.
//-----------------------------------------------------------------------------
#include "BoxCollider.h"

#include "WallCollider.h"


BoxCollider::BoxCollider()
    : m_pBox(nullptr)
{
    m_pCollInfo = new CollisionInfo;
    m_pCollInfo->m_collType = CollisionInfo::CollisionType::Box;
}

BoxCollider::~BoxCollider()
{
    if (m_pCollInfo != nullptr)
    {
        delete m_pCollInfo;
    }
    if (m_pBox != nullptr)
    {
        delete m_pBox;
    }
}

void BoxCollider::Init(const VECTOR& _pos, const VECTOR& _scale, const ObjectTag& _tag, std::function<void()> _func)
{
    m_func = _func;
    m_onCollisionFlag = true;
    m_ownTag = _tag;
    if (m_pBox == nullptr)
    {
        m_pBox = new Box(_pos, _scale);
    }
}

bool BoxCollider::HitCheck(BoxCollider* _other)
{
    const Box& otherBox = *_other->GetBoxAddress();
    const Box& ownBox = *m_pBox;

    // �Փ˂��������ׂ�
    bool result = Intersect(ownBox, otherBox, *m_pCollInfo);
    if (result)
    {
        // �����߂��ʂ��v�Z
        CalcCollisionFixVec(ownBox, otherBox, m_pCollInfo->m_fixVec);
        // �����߂���������
        m_func();
        // ���������l�̃^�O��Ⴄ
        m_onCollisionTag = _other->m_ownTag;
    }
    return result;
}

bool BoxCollider::HitCheck(WallCollider* _other)
{
    const Wall& otherWall = *_other->GetWallAdress();
    const Box& ownBox = *m_pBox;

    // �Փ˂��������ׂ�
    bool result = Intersect(ownBox, otherWall, *m_pCollInfo);
    if (result)
    {
        // �����߂��ʂ��v�Z
        CalcCollisionFixVec(ownBox, otherWall, m_pCollInfo->m_fixVec);
        // �����߂���������
        m_func();

        // ���������l�̃^�O��Ⴄ
        m_onCollisionTag = ObjectTag::Wall;
    }
    return result;
}
