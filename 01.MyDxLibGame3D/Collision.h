//-----------------------------------------------------------------------------
// @brief  衝突判定の基礎クラス定義ヘッダー.
//-----------------------------------------------------------------------------
#pragma once
#include <limits>
#include <functional>
#include <DxLib.h>


// 衝突情報
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

    VECTOR m_collisionPoint;    // 衝突点
    VECTOR m_fixVec;            // 押し戻しベクトル
    VECTOR m_hitNormal;         // 衝突点での法線

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

// 球体
class Sphere
{
public:
    /// コンストラクタ
    Sphere(const VECTOR& _center, float _radius)
        : m_center(_center)
        , m_radius(_radius)
    {
    }

    // コライダー位置の更新
    // 当たり判定の中心
    void UpdateSphere(const VECTOR& _center)
    {
        m_center = _center;
    }

    // 半径の大きさの更新
    // 中心からの半径
    void Radius(float _radius)
    {
        m_radius = _radius;
    }

    VECTOR m_center;    // 中心位置
    float m_radius;     // 半径
};

// ボックス（Box）
class Box
{
public:
    // コンストラクタ
    Box(const VECTOR& _center, const VECTOR& _scale)
    {
        m_scale = _scale;
        UpdateMinMax(_center);
    }

    // コライダー位置の更新処理
    void UpdateMinMax(const VECTOR& _center);

    // サイズの変更をセット(全ての方向にサイズが同じ場合)
    void Scaling(float _x, float _y, float _z);
    // サイズの変更をセット(サイズが異なる場合)
    void Scaling(float _scale);

    VECTOR m_center;        // ボックスの中心点
    VECTOR m_min;           // ボックス最小座標
    VECTOR m_max;           // ボックス最大座標

    VECTOR m_scale;         // ボックスのサイズ
};

// 壁(Wall)
class Wall
{
public:
    // コンストラクタ
    Wall(const VECTOR& _start, const VECTOR& _end, const float& _height);

    VECTOR m_direction;     // 向き
    VECTOR m_start;         // 開始点
    VECTOR m_end;           // 終了点
    float m_height;         // 高さ
};

bool Intersect(const Box& _b1, const Box& _b2, CollisionInfo& _info);
bool Intersect(const Box& _b, const Wall& _w, CollisionInfo& _info);
bool Intersect(const Wall& _w, const Box& _b, CollisionInfo& _info);

void CalcCollisionFixVec(const Box& _box1, const Box& _box2, VECTOR& _calcFixVec); // Boxのめり込み(Box)をもどす量を計算
void CalcCollisionFixVec(const Box& _b, const Wall& _w, VECTOR& _calcFixVec);   // Boxのめり込み(Wall)を戻す量を計算
void CalcCollisionFixVec(const Wall& _w, const Box& _b, VECTOR& _calcFixVec);   // Wallのめり込み(Box)を戻す量を計算

// 当たり判定に使った数学関数
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