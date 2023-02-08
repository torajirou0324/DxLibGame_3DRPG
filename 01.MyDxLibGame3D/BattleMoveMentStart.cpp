//-----------------------------------------------------------------------------
// @brief  �S�L�����s���������s�N���X.
//-----------------------------------------------------------------------------
#include "BattleMoveMentStart.h"
#include "Player.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleMoveMentStart::BattleMoveMentStart()
    : m_enemyAllDeadFlag(false)
    , m_playerDeadFlag(false)
{
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleMoveMentStart::~BattleMoveMentStart()
{
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleMoveMentStart::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
    m_enemyAllDeadFlag = true;
    m_playerDeadFlag = false;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleMoveMentStart::Update()
{
    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        // �s�����I����Ă��Ȃ����A����ł��Ȃ��Ƃ��s������
        if (!m_pCharacter[i]->GetActionFlag() && !m_pCharacter[i]->GetDeathFlag())
        {
            m_pCharacter[i]->Action();
            m_pCharacter[i]->Attack();
            m_pPlayScene->SetAttackObjectAddress(m_pCharacter[i]);    // ���ݍs�����Ă���L�����N�^�[��������
            break;
        }
    }

    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        if (!m_pCharacter[i]->GetDeathFlag())
        {
            // �G�����ݎ���ł��Ȃ���
            if (m_pCharacter[i]->GetAllStatus().HP <= 0 && m_pCharacter[i]->GetCharaName() == CharacterName::UnHuman)
            {
                // ����ł����玀�S�t���O�𗧂āA�v���C���[�Ɏ��g�̕t�^�\��o���l�����Z����
                m_pCharacter[i]->Dead();
                int EXP = m_pCharacter[i]->GetAllStatus().EXP;
                auto player = dynamic_cast<Player*>(m_pCharacter[0]);
                // �L���X�g�����s�����甲����
                if (player == nullptr)
                {
                    break;
                }
                player->EXPAdd(EXP);
            }
            else if(m_pCharacter[i]->GetCharaName() == CharacterName::UnHuman)
            {
                // �G��1�l�ł������Ă��邽��false����
                m_enemyAllDeadFlag = false;
            }
            // �v���C���[������ł��Ȃ���
            if (m_pCharacter[i]->GetAllStatus().HP <= 0 && m_pCharacter[i]->GetCharaName() == CharacterName::Human)
            {
                // ����ł��邽�߃t���O�𗧂Ă�
                m_pCharacter[i]->Dead();
            }
        }
        else
        {
            m_pCharacter[i]->Action();
        }
    }

    // �v���C���[�����ݎ���ł��Ȃ���
    if (m_pCharacter[0]->GetDeathFlag())
    {
        // ����ł��邽�ߔs�k������
        return TAG_BattleState::Defeat;
    }
    // �G���S�ł��Ă��Ȃ���
    if (m_enemyAllDeadFlag)
    {
        // ����ł��邽�ߏ���������
        return TAG_BattleState::Victory;
    }

    // ���݂̍s�����̃L�����N�^�[�s�������ҋ@������
    return TAG_BattleState::MoveMentEnd;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleMoveMentStart::Draw()
{
    printfDx("�S�L�����s������");
}
