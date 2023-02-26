#include "Collision.h"
#include <math.h>

void Box::UpdateMinMax(const VECTOR& _center)
{
    // �傫���𔼕��ɂ��čő�̓_�ƍŏ��̓_�����߂�
    VECTOR scale = VGet(m_scale.x / 2.0f, m_scale.y, m_scale.z / 2.0f);

    m_min = VGet(_center.x - scale.x, _center.y, _center.z - scale.z);
    m_max = VGet(_center.x + scale.x, _center.y + scale.y, _center.z + scale.z);

    m_center = _center;
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

Wall::Wall(const VECTOR& _start, const VECTOR& _end, const float& _height)
{
    m_start = _start;
    m_end = _end;
    m_height = _height;
}

bool Intersect(const Box& _b1, const Box& _b2, CollisionInfo& _info)
{
    bool result = _b1.m_max.x < _b2.m_min.x ||
        _b1.m_max.y < _b2.m_min.y ||
        _b1.m_max.z < _b2.m_min.z ||
        _b2.m_max.x < _b1.m_min.x ||
        _b2.m_max.y < _b1.m_min.y ||
        _b2.m_max.z < _b1.m_min.z;

    // 1��true��Ԃ��Ȃ���΁A2�͏Փ˂��Ă���
    return !result;
}

bool Intersect(const Box& _b, const Wall& _w, CollisionInfo& _info)
{
    VECTOR wallMin = _w.m_start;
    VECTOR wallMax = VGet(_w.m_end.x, _w.m_end.y + _w.m_height, _w.m_end.z);

    bool result = _b.m_max.x < wallMin.x ||
        _b.m_max.y < wallMin.y ||
        _b.m_max.z < wallMin.z ||
        wallMax.x < _b.m_min.x ||
        wallMax.y < _b.m_min.y ||
        wallMax.z < _b.m_min.z;

    // 1��true��Ԃ��Ȃ���΁A2�͏Փ˂��Ă���
    return !result;
}

bool Intersect(const Wall& _w, const Box& _b, CollisionInfo& _info)
{
    VECTOR wallMin = _w.m_start;
    VECTOR wallMax = VGet(_w.m_end.x, _w.m_end.y + _w.m_height, _w.m_end.z);

    bool result = _b.m_max.x < wallMin.x ||
        _b.m_max.y < wallMin.y ||
        _b.m_max.z < wallMin.z ||
        wallMax.x < _b.m_min.x ||
        wallMax.y < _b.m_min.y ||
        wallMax.z < _b.m_min.z;

    // 1��true��Ԃ��Ȃ���΁A2�͏Փ˂��Ă���
    return !result;
}

void CalcCollisionFixVec(const Box& _box1, const Box& _box2, VECTOR& _calcFixVec)
{
    // �߂荞�ݗʂ�߂�
    _calcFixVec = VGet(0.0f, 0.0f, 0.0f);
    // �ʒu���ŏ��̓_�ƍő�̓_�S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = _box2.m_min.x - _box1.m_max.x;
    float dx2 = _box2.m_max.x - _box1.m_min.x;
    float dy1 = _box2.m_min.y - _box1.m_max.y;
    float dy2 = _box2.m_max.y - _box1.m_min.y;
    float dz1 = _box2.m_min.y - _box1.m_max.z;
    float dz2 = _box2.m_max.z - _box1.m_min.z;

    // dx,dy,dz�̂��ꂼ��1��2�̂�����Βl���������ق����Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dx1 : dz2;

    // x,y,z�̂��������Ƃ��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) < CollMath::Abs(dz) && dx != 0.0f)
    {
        _calcFixVec.x = dx;
    }
    if (CollMath::Abs(dx) > CollMath::Abs(dz) && dx != 0.0f)
    {
        _calcFixVec.z = dz;
    }
}

void CalcCollisionFixVec(const Box& _b, const Wall& _w, VECTOR& _calcFixVec)
{
    VECTOR wallMin = _w.m_start;
    VECTOR wallMax = VGet(_w.m_end.x, _w.m_end.y + _w.m_height, _w.m_end.z);

    // �߂荞�ݗʂ�߂�
    _calcFixVec = VGet(0.0f, 0.0f, 0.0f);
    // �ʒu���ŏ��̓_�ƍő�̓_�S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = wallMin.x - _b.m_max.x;
    float dx2 = wallMax.x - _b.m_min.x;
    float dy1 = wallMin.y - _b.m_max.y;
    float dy2 = wallMax.y - _b.m_min.y;
    float dz1 = wallMin.z - _b.m_max.z;
    float dz2 = wallMax.z - _b.m_min.z;

    // dx,dy,dz�̂��ꂼ��1��2�̂�����Βl���������ق����Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x,y,z�̂��������Ƃ��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) < CollMath::Abs(dz) && dx != 0.0f)
    {
        _calcFixVec.x = dx;
    }
    if (CollMath::Abs(dx) > CollMath::Abs(dz) && dx != 0.0f)
    {
        _calcFixVec.z = dz;
    }
}

void CalcCollisionFixVec(const Wall& _w, const Box& _b, VECTOR& _calcFixVec)
{
    VECTOR wallMin = _w.m_start;
    VECTOR wallMax = VGet(_w.m_end.x, _w.m_end.y + _w.m_height, _w.m_end.z);

    // �߂荞�ݗʂ�߂�
    _calcFixVec = VGet(0.0f, 0.0f, 0.0f);
    // �ʒu���ŏ��̓_�ƍő�̓_�S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = _b.m_min.x - wallMax.x;
    float dx2 = _b.m_max.x - wallMin.x;
    float dy1 = _b.m_min.y - wallMax.y;
    float dy2 = _b.m_max.y - wallMin.y;
    float dz1 = _b.m_min.z - wallMax.z;
    float dz2 = _b.m_max.z - wallMin.z;

    // dx,dy,dz�̂��ꂼ��1��2�̂�����Βl���������ق����Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x,y,z�̂��������Ƃ��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) < CollMath::Abs(dz) && dx != 0.0f)
    {
        _calcFixVec.x = dx;
    }
    if (CollMath::Abs(dx) > CollMath::Abs(dz) && dx != 0.0f)
    {
        _calcFixVec.z = dz;
    }
}
