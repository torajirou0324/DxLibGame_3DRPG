//-----------------------------------------------------------------------------
// @brief  エネミークラス.
//-----------------------------------------------------------------------------
#include "Enemy.h"
#include <DxLib.h>
#include "Player.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Enemy::Enemy()
{
	// プレイヤーじゃないです
	m_isPlayerFlag = false;
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Enemy::~Enemy()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void Enemy::Init(std::string name, int level, VECTOR position)
{
    m_name = name;

    m_status.LV = level;
    m_status.HP = 10 + 2 * level;
    m_status.ATK = 2 + level;
    m_status.DEF = 2 + level;
	m_status.INT = 2 + level;
	m_status.RES = 2 + level;
    m_status.AGL = 2 + 2 * level;
    m_status.EXP = level;

    m_hpMax = m_status.HP;
    m_isDeathFlag = false;

    m_position = position;
    // ３Dモデルのポジション設定
    MV1SetPosition(m_modelHandle, m_position);
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void Enemy::Update()
{
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void Enemy::Draw()
{

}

void Enemy::Move()
{
}

//-----------------------------------------------------------------------------
// @brief  アニメーション処理.
//-----------------------------------------------------------------------------
void Enemy::Animation()
{
	// アニメーション繰り返し処理
	if (m_animTotalTime < m_animTime && m_animType == Anim::Attack || m_animTotalTime < m_animTime && m_animType == Anim::Damage)
	{
		m_animType = Anim::Idle;
		m_attackNow = false;
	}
	else if (m_animTotalTime < m_animTime)
	{
		m_animTime = 0.0f;
		if (m_animType == Anim::Death)
		{
			m_animTime = m_animTotalTime;
		}
	}

	// アニメーション切り替え処理
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_modelHandle, 0);
		auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
		m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}

	// 現在のアニメーションフレームをモデルにアタッチする
	MV1SetAttachAnimTime(m_modelHandle, 0, m_animTime);

	// アニメーションフレーム加算
	m_animTime += 0.3f;
}
