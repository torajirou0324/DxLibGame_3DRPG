//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̑f������r�����N���X.
//-----------------------------------------------------------------------------
#include "BattleComparison.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleComparison::BattleComparison()
{
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleComparison::~BattleComparison()
{
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleComparison::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleComparison::Update()
{
    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        for (int j = 0; j < m_pCharacter.size(); j++)
        {
            if (i == j)
            {

            }
            else
            {
                if (m_pCharacter[i]->GetAllStatus().AGL > m_pCharacter[j]->GetAllStatus().AGL)
                {
                    if (i < j)
                    {

                    }
                    else
                    {
                        auto tmp = m_pCharacter[i];
                        m_pCharacter[i] = m_pCharacter[j];
                        m_pCharacter[j] = tmp;
                    }
                }
            }
        }
    }

    return TAG_BattleState::MoveMentStart;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleComparison::Draw()
{
    printfDx("�f������r����");
}