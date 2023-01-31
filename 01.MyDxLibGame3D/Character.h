//-----------------------------------------------------------------------------
// @brief  �v���C���[�ƃG�l�~�[�̊��N���X.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <DxLib.h>
#include "Status.h"

// �A�j���[�V�����Ǘ��\����
enum Anim
{
    Idle,               // �ҋ@
    Walk,               // ����
    Attack,             // �U��
    Damage,             // ��_��
    Death               // ���S
};

class Character
{
public:
    Character()
        : m_modelHandle(-1)
        , m_hpMax(0)
        , m_animTime(0.0f)
        , m_animTotalTime(0.0f)
        , m_isDeath(false)
        , m_name("")
        , m_position(VGet(0.0f,0.0f,0.0f))
        , m_status()
        , m_animType(Idle)
        , m_beforeAnimType(Idle)
    {}
    virtual ~Character(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;

    void Attack()           // �G�l�~�[����v���C���[�֍U���p����
    {
        Player::Damage(m_status.ATK);
    }

    void Damage(int atk)    // ��_�������i���Ή��j
    {
        int HP = m_status.HP;
        HP = HP - atk;
        if (HP < 0)
        {
            HP = 0;
        }
        m_status.HP = HP;
    }

    bool GetDeathFlag()     // ����ł��邩�ǂ���
    {
        return m_isDeath;
    }

    // �Q�b�^�[
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_status; }
    const int& GetHPMAX() { return m_hpMax; }
protected:
    int m_modelHandle;      // �L�����N�^�[���g�̃��f���n���h��
    int m_hpMax;            // �L�����N�^�[�̍ő�HP�ۑ��p

    float m_animTime;       // �A�j���[�V�����̌o�ߎ���
    float m_animTotalTime;  // �A�j���[�V�����̑��Đ�����

    bool m_isDeath;         // ���񂾂��ǂ���

    std::string m_name;     // �L�����N�^�[�̖��O
    VECTOR m_position;      // �L�����N�^�[�̍��W
    Status m_status;        // �L�����N�^�[�̃X�e�[�^�X

    Anim m_animType;        // ���݂̃A�j���[�V�����ۑ��p
    Anim m_beforeAnimType;  // 1�O�̃A�j���[�V�����ۑ��p
};