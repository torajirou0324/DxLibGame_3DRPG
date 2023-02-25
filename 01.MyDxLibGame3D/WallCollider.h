//-----------------------------------------------------------------------------
// @brief  壁の当たり判定クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "ColliderBase.h"

class WallCollider : public ColliderBase
{
public:
    WallCollider();
    ~WallCollider() override;   // 個別クラスがあるので独自で削除を行う

    // 当たり判定を検出(相手のコライダー)
    bool CollisionDetection(ColliderBase* _other) override;

    // 当たり判定結果を返す
    bool HitCheck(class BoxCollider* _other) override;
    bool HitCheck(class WallCollider* _other) override;
};
