//-----------------------------------------------------------------------------
// @brief  ボックスの当たり判定クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "ColliderBase.h"

class BoxCollider : public ColliderBase
{
public:
    BoxCollider();
    ~BoxCollider() override;    // 個別クラスがあるので独自で削除を行う

    void Init(const VECTOR& _pos, const VECTOR& _scale, const ObjectTag& _tag, const CollisionInfo::CollisionType& _type);
    void UpdatePosition(const VECTOR& _pos) { m_pBox->UpdateMinMax(_pos); }

    // 当たり判定を検出(相手のコライダー)
    bool CollisionDetection(ColliderBase* _other) override;

    // 当たり判定結果を返す
    bool HitCheck(class BoxCollider* _other) override;
    bool HitCheck(class WallCollider* _other) override;
private:
    Box* m_pBox;
};