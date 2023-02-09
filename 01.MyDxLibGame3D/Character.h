//-----------------------------------------------------------------------------
// @brief  �v���C���[�ƃG�l�~�[�̊��N���X.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <DxLib.h>
#include "AssetManager.h"
#include "Status.h"

// �v���C���[���G���𔻒肷��p�񋓑�
enum CharacterName
{
    Human,      // �l�i�v���C���[�j
    UnHuman,    // �l�O�i�G�j
};

enum MoveCommand    // �퓬����Ƃ��̍s�����[�V����
{
    Atk,        // �U������
    charge,     // ���߂�i���̃^�[���U����2�{�j
};

// �A�j���[�V�����Ǘ��񋓑�
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
        , m_isDeathFlag(false)
        , m_enActionFlag(false)
        , m_attackNow(false)
        , m_name("")
        , m_position(VGet(0.0f,0.0f,0.0f))
        , m_status()
        , m_basicStatus()
        , m_animType(Idle)
        , m_beforeAnimType(Idle)
        , m_pAttackObject(nullptr)
    {
        // �A�j���[�V������ۑ�
        m_animHandle[0] = AssetManager::UseModel(AssetManager::AnimIdle);
        m_animHandle[1] = AssetManager::UseModel(AssetManager::AnimWalk);
        m_animHandle[2] = AssetManager::UseModel(AssetManager::AnimAttack);
        m_animHandle[3] = AssetManager::UseModel(AssetManager::AnimDamage);
        m_animHandle[4] = AssetManager::UseModel(AssetManager::AnimDeath);
    }
    virtual ~Character(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;

    virtual void Move() = 0;

    void Attack()           // �G�l�~�[����v���C���[�֍U���p����
    {
        int ATK = m_status.ATK;
        int DEF = m_pAttackObject->GetAllStatus().DEF;
        ATK = ATK - DEF;
        if (ATK < 1)
        {
            ATK = 1;
        }
        m_animType = Anim::Attack;  // �U���A�j���[�V�����J�n
        m_attackNow = true;
        m_pAttackObject->Damage(ATK);
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

        m_animType = Anim::Damage;  // ��_���A�j���[�V�����J�n
    }

    void Dead()             // ���ʂƂ��ɌĂ�(���Ή�)
    {
        m_isDeathFlag = true;
        m_animType = Anim::Death;
    }

    void ActionInit()       // �s���\��
    {
        m_enActionFlag = false;
    }

    void Action()           // �s���ς�
    {
        m_enActionFlag = true;
    }

    // �Z�b�^�[
    void SetAttackObjectAddress(Character* _AttackObject) { m_pAttackObject = _AttackObject; }

    // �Q�b�^�[
    const bool &GetDeathFlag()          // ����ł��邩�ǂ���
    {
        return m_isDeathFlag;
    }
    const bool &GetActionFlag()         // �s��������
    {
        return m_enActionFlag;
    }
    const bool& GetAttackNowFlag()      // �U�������ǂ���
    {
        return m_attackNow;
    }
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_status; }
    const CharacterName& GetCharaName() const { return m_CharaName; }
    const int& GetHPMAX() { return m_hpMax; }
protected:
    int m_animHandle[5];	    // �A�j���[�V�����̃��f���n���h��.
    int m_modelHandle;          // �L�����N�^�[���g�̃��f���n���h��
    int m_hpMax;                // �L�����N�^�[�̍ő�HP�ۑ��p

    float m_animTime;           // �A�j���[�V�����̌o�ߎ���
    float m_animTotalTime;      // �A�j���[�V�����̑��Đ�����

    bool m_isDeathFlag;         // ���񂾂��ǂ���
    bool m_enActionFlag;        // �s�����I�������
    bool m_attackNow;           // �U�������ǂ���

    std::string m_name;         // �L�����N�^�[�̖��O

    VECTOR m_position;          // �L�����N�^�[�̍��W

    Status m_status;            // �L�����N�^�[�̃X�e�[�^�X�i�퓬���ω��p�j
    Status m_basicStatus;       // �L�����N�^�[�X�e�[�^�X�i��b�X�e�[�^�X�j

    Anim m_animType;            // ���݂̃A�j���[�V�����ۑ��p
    Anim m_beforeAnimType;      // 1�O�̃A�j���[�V�����ۑ��p

    MoveCommand m_moveSelection;// �s�����ǂ������߂�
    CharacterName m_CharaName;  // �L�����N�^�[���l���l�O������p
private:
    Character* m_pAttackObject; // �U�����鑊��i�[�p�ϐ�
};