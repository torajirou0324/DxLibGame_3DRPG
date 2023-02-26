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

    void Init(const VECTOR& _pos, const VECTOR& _scale, const ObjectTag& _tag);
    void UpdatePosition(const VECTOR& _pos) { m_pBox->UpdateMinMax(_pos); }

    // 当たり判定を検出(相手のコライダー)
    // 当たり判定結果を返す
    bool HitCheck(class BoxCollider* _other) override;
    bool HitCheck(class WallCollider* _other) override;

    // ゲッター
    const Box* GetBoxAddress() const { return m_pBox; }
private:
    Box* m_pBox;
};