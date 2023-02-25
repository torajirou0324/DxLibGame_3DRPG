#include "BoxCollider.h"

BoxCollider::BoxCollider()
    : m_pBox(nullptr)
{
}

BoxCollider::~BoxCollider()
{
    if (m_pBox != nullptr)
    {
        delete m_pBox;
    }
}

void BoxCollider::Init(const VECTOR& _pos, const VECTOR& _scale, const ObjectTag& _tag, const CollisionInfo::CollisionType& _type)
{
    m_onCollisionTag = _tag;

    m_pCollInfo = new CollisionInfo;
    m_pCollInfo->m_collType = _type;
    m_pBox = new Box(_pos, _scale);
}

bool BoxCollider::CollisionDetection(ColliderBase* _other)
{
    return _other->HitCheck(this);
}

bool BoxCollider::HitCheck(BoxCollider* _other)
{
    return false;
}

bool BoxCollider::HitCheck(WallCollider* _other)
{
    return false;
}
