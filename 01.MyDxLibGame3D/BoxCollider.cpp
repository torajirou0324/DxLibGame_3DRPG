//-----------------------------------------------------------------------------
// @brief  ボックスの当たり判定クラス.
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

void BoxCollider::Init(const VECTOR& _pos, const VECTOR& _scale, const ObjectTag& _tag)
{
    m_onCollisionFlag = true;
    m_onCollisionTag = _tag;
    m_pBox = new Box(_pos, _scale);
}

bool BoxCollider::HitCheck(BoxCollider* _other)
{
    const Box& otherBox = *_other->GetBoxAddress();
    const Box& ownBox = *m_pBox;

    bool result = Intersect(otherBox, ownBox, *m_pCollInfo);
    if (result)
    {
        CalcCollisionFixVec(ownBox, otherBox, m_pCollInfo->m_fixVec);
        // 当たった人のタグを貰う
        m_onCollisionTag = _other->m_onCollisionTag;
    }
    return result;
}

bool BoxCollider::HitCheck(WallCollider* _other)
{
    const Wall& otherWall = *_other->GetWallAdress();
    const Box& ownBox = *m_pBox;

    bool result = Intersect(ownBox, otherWall, *m_pCollInfo);
    if (result)
    {
        CalcCollisionFixVec(ownBox, otherWall, m_pCollInfo->m_fixVec);
    }
    return result;
}
