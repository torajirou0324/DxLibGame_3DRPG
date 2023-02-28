//-----------------------------------------------------------------------------
// @brief  �S�L�����s�������ҋ@�����N���X.
//-----------------------------------------------------------------------------
#include "BattleMoveMentEnd.h"

#include "BattleEventManager.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleMoveMentEnd::BattleMoveMentEnd(class BattleEventManager* _manager)
{
    m_pBattleManager = _manager;
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
void BattleMoveMentEnd::Init()
{
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleMoveMentEnd::Update()
{
    if (!m_pBattleManager->m_pAttackNowCharacter->GetAttackNowFlag())
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
    printfDx("�S�L�����s�������ҋ@����\n");
    printfDx("%s:%d", m_pBattleManager->m_pAttackNowCharacter->GetName().c_str(), m_pBattleManager->m_pAttackNowCharacter->GetAttackNowFlag());
    DrawFormatString(650, 800, GetColor(255, 255, 255), "%s��%d�̂�������", m_pBattleManager->m_pAttackNowCharacter->GetName().c_str(), m_pBattleManager->m_pAttackNowCharacter->GetAllStatus().ATK);
}
