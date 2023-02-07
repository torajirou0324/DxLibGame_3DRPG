//-----------------------------------------------------------------------------
// @brief  �S�L�����s�������ҋ@�����N���X.
//-----------------------------------------------------------------------------
#include "BattleMoveMentEnd.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleMoveMentEnd::BattleMoveMentEnd()
{
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleMoveMentEnd::~BattleMoveMentEnd()
{
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleMoveMentEnd::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleMoveMentEnd::Update()
{
    if (!m_pCharacterAttackNow->GetAttackNowFlag())
    {
        return TAG_BattleState::Continue;
    }
    return TAG_BattleState::None;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleMoveMentEnd::Draw()
{
    printfDx("�S�L�����s�������ҋ@����");
}
