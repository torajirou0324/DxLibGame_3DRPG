//-----------------------------------------------------------------------------
// @brief  �Փ˔���̊�b�N���X��`�w�b�_�[.
//-----------------------------------------------------------------------------
#pragma once
#include <DxLib.h>

// �Փˏ��
class CollisionInfo
{
public:
    CollisionInfo()
        : m_collType(CollisionType::None)
    {
        VECTOR initPos = VGet(0.0f, 0.0f, 0.0f);

        m_collisionPoint = initPos;
        m_fixVec = initPos;
        m_hitNormal = initPos;
    }

    VECTOR m_collisionPoint;    // �Փ˓_
    VECTOR m_fixVec;            // �����߂��x�N�g��
    VECTOR m_hitNormal;         // �Փ˓_�ł̖@��

    enum class CollisionType
    {
        Sphere,
        Box,
        Wall,
        Ground,
        None
    };
    CollisionType m_collType;
};

// ����
class Sphere
{
public:
    /// �R���X�g���N�^
    Sphere(const VECTOR& _center, float _radius)
        : m_center(_center)
        , m_radius(_radius)
    {
    }

    // �R���C�_�[�ʒu�̍X�V
    // �����蔻��̒��S
    void UpdateSphere(const VECTOR& _center)
    {
        m_center = _center;
    }

    // ���a�̑傫���̍X�V
    // ���S����̔��a
    void Radius(float _radius)
    {
        m_radius = _radius;
    }

    VECTOR m_center;    // ���S�ʒu
    float m_radius;     // ���a
};

// �{�b�N�X�iBox�j
class Box
{
public:
    // �R���X�g���N�^
    Box(const VECTOR& _center, const VECTOR& _scale)
    {
        // �傫���𔼕��ɂ��čő�̓_�ƍŏ��̓_�����߂�
        VECTOR scale = VGet(_scale.x / 2.0f, _scale.y / 2.0f, _scale.z / 2.0f);
        m_min = VGet(_center.x - scale.x, _center.y - scale.y, _center.z - scale.z);
        m_max = VGet(_center.x + scale.x, _center.y + scale.y, _center.z + scale.z);

        m_center = _center;
        m_scale = _scale;
        CalcVertex();
    }

    // �{�b�N�X��8���_���v�Z���ăZ�b�g����֐�
    void CalcVertex();

    // �R���C�_�[�ʒu�̍X�V����
    void UpdateMinMax(const VECTOR& _center);

    // �T�C�Y�̕ύX���Z�b�g(�S�Ă̕����ɃT�C�Y�������ꍇ)
    void Scaling(float _x, float _y, float _z);
    // �T�C�Y�̕ύX���Z�b�g(�T�C�Y���قȂ�ꍇ)
    void Scaling(float _scale);

    VECTOR m_center;        // �{�b�N�X�̒��S�_
    VECTOR m_min;           // �{�b�N�X�ŏ����W
    VECTOR m_max;           // �{�b�N�X�ő���W
    VECTOR m_vertex[8];     // �{�b�N�X�̒��_

    VECTOR m_scale;         // �{�b�N�X�̃T�C�Y
};