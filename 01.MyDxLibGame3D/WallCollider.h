//-----------------------------------------------------------------------------
// @brief  �ǂ̓����蔻��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "ColliderBase.h"

class WallCollider : public ColliderBase
{
public:
    WallCollider();
    ~WallCollider() override;   // �ʃN���X������̂œƎ��ō폜���s��

    // �����蔻������o(����̃R���C�_�[)
    bool CollisionDetection(ColliderBase* _other) override;

    // �����蔻�茋�ʂ�Ԃ�
    bool HitCheck(class BoxCollider* _other) override;
    bool HitCheck(class WallCollider* _other) override;
};
