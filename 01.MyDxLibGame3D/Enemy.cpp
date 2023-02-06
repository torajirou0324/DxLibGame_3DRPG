//-----------------------------------------------------------------------------
// @brief  �G�l�~�[�N���X.
//-----------------------------------------------------------------------------
#include "Enemy.h"
#include <DxLib.h>
#include "Player.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Enemy::Enemy()
{

}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
Enemy::~Enemy()
{
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void Enemy::Init(std::string name, int level, VECTOR position)
{
    m_name = name;
    m_CharaName = UnHuman;

    m_status.LV = level;
    m_status.HP = 10 + 2 * level;
    m_status.ATK = 2 + level;
    m_status.DEF = level;
    m_status.AGL = 2 + 2 * level;
    m_status.EXP = level;

    m_hpMax = m_status.HP;
    m_isDeathFlag = false;

    m_position = position;
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(m_modelHandle, m_position);
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void Enemy::Update()
{
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void Enemy::Draw()
{

}

//-----------------------------------------------------------------------------
// @brief  �A�j���[�V��������.
//-----------------------------------------------------------------------------
void Enemy::Animation()
{
	// �A�j���[�V�����J��Ԃ�����
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

	// �A�j���[�V�����؂�ւ�����
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_modelHandle, 0);
		auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
		m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}

	// ���݂̃A�j���[�V�����t���[�������f���ɃA�^�b�`����
	MV1SetAttachAnimTime(m_modelHandle, 0, m_animTime);

	// �A�j���[�V�����t���[�����Z
	m_animTime += 0.3f;
}
