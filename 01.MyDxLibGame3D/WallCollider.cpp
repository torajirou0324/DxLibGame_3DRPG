//-----------------------------------------------------------------------------
// @brief  壁の当たり判定クラス.
//-----------------------------------------------------------------------------
#include "WallCollider.h"

#include "BoxCollider.h"

WallCollider::WallCollider()
    : m_pWall(nullptr)
{
    m_pCollInfo = new CollisionInfo;
    m_pCollInfo->m_collType = CollisionInfo::CollisionType::Wall;
}

WallCollider::~WallCollider()
{
    if (m_pCollInfo != nullptr)
    {
        delete m_pCollInfo;
    }
    if (m_pWall != nullptr)
    {
        delete m_pWall;
    }
}

void WallCollider::Init(const VECTOR& _start, const VECTOR& _end, const float _height, const ObjectTag& _tag)
{
    m_onCollisionFlag = true;
    m_onCollisionTag = _tag;
    if (m_pWall == nullptr)
    {
        m_pWall = new Wall(_start, _end, _height);
    }

}

bool WallCollider::HitCheck(BoxCollider* _other)
{
    const Box& otherBox = *_other->GetBoxAddress();
    const Wall& ownWall = *m_pWall;

    bool result = Intersect(ownWall, otherBox, _other->GetCollisionInfo());
    if (result)
    {
        CalcCollisionFixVec(ownWall, otherBox, m_pCollInfo->m_fixVec);

        // 当たった人のタグを貰う
        m_onCollisionTag = ObjectTag::Wall;
    }
    return result;
}
