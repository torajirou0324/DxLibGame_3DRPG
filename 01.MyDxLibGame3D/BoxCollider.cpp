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

    // 衝突したか調べる
    bool result = Intersect(ownBox, otherBox, *m_pCollInfo);
    if (result)
    {
        // 押し戻し量を計算
        CalcCollisionFixVec(ownBox, otherBox, m_pCollInfo->m_fixVec);

        // 当たった人のタグを貰う
        m_onCollisionTag = _other->m_ownTag;

        // 押し戻しをかける
        m_func();
    }
    return result;
}

bool BoxCollider::HitCheck(WallCollider* _other)
{
    const Wall& otherWall = *_other->GetWallAdress();
    const Box& ownBox = *m_pBox;

    // 衝突したか調べる
    bool result = Intersect(ownBox, otherWall, *m_pCollInfo);
    if (result)
    {
        // 押し戻し量を計算
        CalcCollisionFixVec(ownBox, otherWall, m_pCollInfo->m_fixVec);

        // 当たった人のタグを貰う
        m_onCollisionTag = ObjectTag::Wall;

        // 押し戻しをかける
        m_func();
    }
    return result;
}
