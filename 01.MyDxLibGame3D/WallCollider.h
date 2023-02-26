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

    void Init(const VECTOR& _start, const VECTOR& _end, const float _height, const ObjectTag& _tag);

    // �����蔻������o(����̃R���C�_�[)
    // �����蔻�茋�ʂ�Ԃ�
    bool HitCheck(class BoxCollider* _other) override;

    // �Q�b�^�[
    const Wall* GetWallAdress() const { return m_pWall; }
private:
    Wall* m_pWall;
};
