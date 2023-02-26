//-----------------------------------------------------------------------------
// @brief  �Փ˔���̊�b�N���X��`�w�b�_�[.
//-----------------------------------------------------------------------------
#pragma once
#include <DxLib.h>
#include <limits>

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
        m_scale = _scale;
        UpdateMinMax(_center);
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

// ��(Wall)
class Wall
{
public:
    // �R���X�g���N�^
    Wall(const VECTOR& _start, const VECTOR& _end, const float& _height);

    VECTOR m_direction;     // ����
    VECTOR m_start;         // �J�n�_
    VECTOR m_end;           // �I���_
    float m_height;         // ����
    float m_planeD;         // ���ʕ�������d�l
    float m_yRotate;        // Y����]�p
};

bool Intersect(const Box& _b1, const Box& _b2, CollisionInfo& _info);
bool Intersect(const Box& _b, const Wall& _w, CollisionInfo& _info);
bool Intersect(const Wall& _w, const Box& _b, CollisionInfo& _info);

void CalcCollisionFixVec(const Box& _box1, const Box& _box2, VECTOR& _calcFixVec); // Box�̂߂荞��(Box)�����ǂ��ʂ��v�Z
void CalcCollisionFixVec(const Box& _b, const Wall& _w, VECTOR& _calcFixVec);   // Box�̂߂荞��(Wall)��߂��ʂ��v�Z
void CalcCollisionFixVec(const Wall& _w, const Box& _b, VECTOR& _calcFixVec);   // Wall�̂߂荞��(Box)��߂��ʂ��v�Z

// �����蔻��Ɏg�������w�֐�
namespace CollMath
{
    const float m_pi = 3.1415926535f;
    const float m_twoPi = m_pi * 2.0f;
    const float m_piOver2 = m_pi / 2.0f;
    const float m_infinity = std::numeric_limits<float>::infinity();
    const float m_negInfinity = -std::numeric_limits<float>::infinity();
    const VECTOR m_unitX = VGet(1.0f, 0.0f, 0.0f);
    const VECTOR m_unitY = VGet(0.0f, 1.0f, 0.0f);
    const VECTOR m_unitZ = VGet(0.0f, 0.0f, 1.0f);

    inline float Abs(float _value)
    {
        return fabs(_value);
    }
}