//-----------------------------------------------------------------------------
// @brief  �{�b�N�X�̓����蔻��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "ColliderBase.h"

class BoxCollider : public ColliderBase
{
public:
    BoxCollider();
    ~BoxCollider() override;    // �ʃN���X������̂œƎ��ō폜���s��

    void Init(const VECTOR& _pos, const VECTOR& _scale, const ObjectTag& _tag, const CollisionInfo::CollisionType& _type);
    void UpdatePosition(const VECTOR& _pos) { m_pBox->UpdateMinMax(_pos); }

    // �����蔻������o(����̃R���C�_�[)
    bool CollisionDetection(ColliderBase* _other) override;

    // �����蔻�茋�ʂ�Ԃ�
    bool HitCheck(class BoxCollider* _other) override;
    bool HitCheck(class WallCollider* _other) override;
private:
    Box* m_pBox;
};