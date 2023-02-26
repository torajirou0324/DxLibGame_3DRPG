#include "Collision.h"
#include <math.h>

void Box::CalcVertex()
{
    // 箱の上側4点
    m_vertex[0] = VGet(m_min.x, m_min.y, m_max.z);
    m_vertex[1] = VGet(m_max.x, m_min.y, m_max.z);
    m_vertex[2] = VGet(m_min.x, m_max.y, m_max.z);
    m_vertex[3] = VGet(m_max.x, m_max.y, m_max.z);

    // 箱の下側4点VECTOR
    m_vertex[4] = VGet(m_min.x, m_min.y, m_min.z);
    m_vertex[5] = VGet(m_max.x, m_min.y, m_min.z);
    m_vertex[6] = VGet(m_min.x, m_max.y, m_min.z);
    m_vertex[7] = VGet(m_max.x, m_max.y, m_min.z);
}

void Box::UpdateMinMax(const VECTOR& _center)
{
    // 大きさを半分にして最大の点と最小の点を決める
    VECTOR scale = VGet(m_scale.x / 2.0f, m_scale.y, m_scale.z / 2.0f);

    m_min = VGet(_center.x - scale.x, _center.y, _center.z - scale.z);
    m_max = VGet(_center.x + scale.x, _center.y + scale.y, _center.z + scale.z);

    m_center = _center;

    CalcVertex();
}

void Box::Scaling(float _x, float _y, float _z)
{
    float revision = 10.0f;

    // もらった大きさに補正をかける
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

    // 壁面の表面ベクトルを求める
    VECTOR nomalizeWallLine = VSub(_end, _start);
    nomalizeWallLine = VNorm(nomalizeWallLine);

    // 壁面の平面方程式
    m_direction = VCross(CollMath::m_unitY, nomalizeWallLine);
    m_planeD = -1.0f * VDot(m_direction, _start);

    // 表示回転角と回転方向
    VECTOR sgnVec = VCross(CollMath::m_unitY, nomalizeWallLine);
    float yAngle = acosf(VDot(CollMath::m_unitY, nomalizeWallLine)) - CollMath::m_piOver2;

    m_yRotate = sgnVec.z > 0 ? yAngle : -yAngle + CollMath::m_pi;
}

bool Intersect(const Box& _b1, const Box& _b2, CollisionInfo& _info)
{
    bool result = _b1.m_max.x < _b2.m_min.x ||
        _b1.m_max.y < _b2.m_min.y ||
        _b1.m_max.z < _b2.m_min.z ||
        _b2.m_max.x < _b1.m_min.x ||
        _b2.m_max.y < _b1.m_min.y ||
        _b2.m_max.z < _b1.m_min.z;

    // 1つもtrueを返さなければ、2つは衝突している
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

    // 1つもtrueを返さなければ、2つは衝突している
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

    // 1つもtrueを返さなければ、2つは衝突している
    return !result;
}

void CalcCollisionFixVec(const Box& _box1, const Box& _box2, VECTOR& _calcFixVec)
{
    // めり込み量を戻す
    _calcFixVec = VGet(0.0f, 0.0f, 0.0f);
    // 位置が最小の点と最大の点全ての距離パターンを調べる
    float dx1 = _box2.m_min.x - _box1.m_max.x;
    float dx2 = _box2.m_max.x - _box1.m_min.x;
    float dy1 = _box2.m_min.y - _box1.m_max.y;
    float dy2 = _box2.m_max.y - _box1.m_min.y;
    float dz1 = _box2.m_min.y - _box1.m_max.z;
    float dz2 = _box2.m_max.z - _box1.m_min.z;

    // dx,dy,dzのそれぞれ1と2のうち絶対値が小さいほうをセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dx1 : dz2;

    // x,y,zのうちもっとも差が小さい軸で位置を調整
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        _calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        _calcFixVec.y = dy;
    }
    else
    {
        _calcFixVec.z = dz;
    }
}

void CalcCollisionFixVec(const Box& _b, const Wall& _w, VECTOR& _calcFixVec)
{
    VECTOR wallMin = _w.m_start;
    VECTOR wallMax = VGet(_w.m_end.x, _w.m_end.y + _w.m_height, _w.m_end.z);

    // めり込み量を戻す
    _calcFixVec = VGet(0.0f, 0.0f, 0.0f);
    // 位置が最小の点と最大の点全ての距離パターンを調べる
    float dx1 = wallMin.x - _b.m_max.x;
    float dx2 = wallMax.x - _b.m_min.x;
    float dy1 = wallMin.y - _b.m_max.y;
    float dy2 = wallMax.y - _b.m_min.y;
    float dz1 = wallMin.z - _b.m_max.z;
    float dz2 = wallMax.z - _b.m_min.z;

    // dx,dy,dzのそれぞれ1と2のうち絶対値が小さいほうをセットする
    //float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    //float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    //float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dx1 : dz2;

    float dx = -1.0f * (dx1 + dx2);
    float dy = -1.0f * (dy1 + dy2);
    float dz = -1.0f * (dz1 + dz2);

    // x,y,zのうちもっとも差が小さい軸で位置を調整
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz) && dx != 0.0f)
    {
        _calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz) && dy != 0.0f)
    {
        _calcFixVec.y = dy;
    }
    else
    {
        _calcFixVec.z = dz;
    }
}

void CalcCollisionFixVec(const Wall& _w, const Box& _b, VECTOR& _calcFixVec)
{
    VECTOR wallMin = _w.m_start;
    VECTOR wallMax = VGet(_w.m_end.x, _w.m_end.y + _w.m_height, _w.m_end.z);

    // めり込み量を戻す
    _calcFixVec = VGet(0.0f, 0.0f, 0.0f);
    // 位置が最小の点と最大の点全ての距離パターンを調べる
    float dx1 = _b.m_min.x - wallMax.x;
    float dx2 = _b.m_max.x - wallMin.x;
    float dy1 = _b.m_min.y - wallMax.y;
    float dy2 = _b.m_max.y - wallMin.y;
    float dz1 = _b.m_min.z - wallMax.z;
    float dz2 = _b.m_max.z - wallMin.z;

    // dx,dy,dzのそれぞれ1と2のうち絶対値が小さいほうをセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x,y,zのうちもっとも差が小さい軸で位置を調整
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        _calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        _calcFixVec.y = dy;
    }
    else
    {
        _calcFixVec.z = dz;
    }
}
