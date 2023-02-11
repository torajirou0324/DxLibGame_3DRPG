//-----------------------------------------------------------------------------
// @brief  �S�L�����s���������s�N���X.
//-----------------------------------------------------------------------------
#include "BattleMoveMentStart.h"
#include "Player.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleMoveMentStart::BattleMoveMentStart(class PlayScene* _playScene)
    : m_enemyAllDeadFlag(false)
    , m_playerDeadFlag(false)
{
    m_pPlaySceneStorage = _playScene;
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
void BattleMoveMentStart::Init()
{
    m_enemyAllDeadFlag = true;
    m_playerDeadFlag = false;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleMoveMentStart::Update()
{
    auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
    for (int i = 0; i < CharacterALL.size(); i++)
    {
        // �s�����I����Ă��Ȃ����A����ł��Ȃ��Ƃ��s������
        if (!CharacterALL[i]->GetActionFlag() && !CharacterALL[i]->GetDeathFlag())
        {
            CharacterALL[i]->Action();
            CharacterALL[i]->Attack();
            m_pPlaySceneStorage->SetAttackObjectAddress(CharacterALL[i]);    // ���ݍs�����Ă���L�����N�^�[��������
            break;
        }
    }

    for (int i = 0; i < CharacterALL.size(); i++)
    {
        if (!CharacterALL[i]->GetDeathFlag())
        {
            // �G�����ݎ���ł��Ȃ���
            if (CharacterALL[i]->GetAllStatus().HP <= 0 && !CharacterALL[i]->GetDiscrimination())
            {
                // ����ł����玀�S�t���O�𗧂āA�v���C���[�Ɏ��g�̕t�^�\��o���l�����Z����
                CharacterALL[i]->Dead();
                int EXP = CharacterALL[i]->GetAllStatus().EXP;
                auto player = dynamic_cast<Player*>(CharacterALL[0]);
                // �L���X�g�����s�����甲����
                if (player == nullptr)
                {
                    break;
                }
                player->EXPAdd(EXP);
            }
            else if(!CharacterALL[i]->GetDiscrimination())
            {
                // �G��1�l�ł������Ă��邽��false����
                m_enemyAllDeadFlag = false;
            }
            // �v���C���[������ł��Ȃ���
            if (CharacterALL[i]->GetAllStatus().HP <= 0 && CharacterALL[i]->GetDiscrimination())
            {
                // ����ł��邽�߃t���O�𗧂Ă�
                CharacterALL[i]->Dead();
            }
        }
        else
        {
            CharacterALL[i]->Action();
        }
    }

    // �v���C���[�����ݎ���ł��Ȃ���
    if (CharacterALL[0]->GetDeathFlag())
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
