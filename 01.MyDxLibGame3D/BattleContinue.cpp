//-----------------------------------------------------------------------------
// @brief  �^�[���p�������N���X.
//-----------------------------------------------------------------------------
#include "BattleContinue.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleContinue::BattleContinue()
{
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleContinue::~BattleContinue()
{
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleContinue::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleContinue::Update()
{
    // �S���̃A�N�V�������I���܂ōs�����s�����֖߂�
    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        if (!m_pCharacter[i]->GetActionFlag())
        {
            return TAG_BattleState::MoveMentStart;
        }
    }

    // �S�Ă̍s���������������Ă���G�������Ă��邽�߃R�}���h�����֖߂�O�ɍs���t���O��false�ɖ߂�
    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        m_pCharacter[i]->ActionInit();
    }
    return TAG_BattleState::Command;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleContinue::Draw()
{
    printfDx("�o�g���p�����菈��");
}