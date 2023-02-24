#include "Collision.h"

void Box::CalcVertex()
{
    // ���̏㑤4�_
    m_vertex[0] = VGet(m_min.x, m_min.y, m_max.z);
    m_vertex[1] = VGet(m_max.x, m_min.y, m_max.z);
    m_vertex[2] = VGet(m_min.x, m_max.y, m_max.z);
    m_vertex[3] = VGet(m_max.x, m_max.y, m_max.z);

    // ���̉���4�_VECTOR
    m_vertex[4] = VGet(m_min.x, m_min.y, m_min.z);
    m_vertex[5] = VGet(m_max.x, m_min.y, m_min.z);
    m_vertex[6] = VGet(m_min.x, m_max.y, m_min.z);
    m_vertex[7] = VGet(m_max.x, m_max.y, m_min.z);
}

void Box::UpdateMinMax(const VECTOR& _center)
{
    // �傫���𔼕��ɂ��čő�̓_�ƍŏ��̓_�����߂�
    VECTOR scale = VGet(m_scale.x / 2.0f, m_scale.y / 2.0f, m_scale.z / 2.0f);
    m_min = VGet(_center.x - scale.x, _center.y - scale.y, _center.z - scale.z);
    m_max = VGet(_center.x + scale.x, _center.y + scale.y, _center.z + scale.z);

    m_center = _center;

    CalcVertex();
}

void Box::Scaling(float _x, float _y, float _z)
{
    float revision = 10.0f;

    // ��������傫���ɕ␳��������
    m_scale = VGet(_x * revision, _y * revision, _z * revision);
}

void Box::Scaling(float _scale)
{
    Scaling(_scale, _scale, _scale);
}
