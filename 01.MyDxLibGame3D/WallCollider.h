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

    void Init(const VECTOR& _start, const VECTOR& _end, const float _height, const ObjectTag& _tag);

    // 当たり判定を検出(相手のコライダー)
    // 当たり判定結果を返す
    bool HitCheck(class BoxCollider* _other) override;

    // ゲッター
    const Wall* GetWallAdress() const { return m_pWall; }
private:
    Wall* m_pWall;
};
