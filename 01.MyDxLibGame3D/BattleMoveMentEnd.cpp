//-----------------------------------------------------------------------------
// @brief  全キャラ行動完了待機処理クラス.
//-----------------------------------------------------------------------------
#include "BattleMoveMentEnd.h"

#include "BattleEventManager.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleMoveMentEnd::BattleMoveMentEnd(class BattleEventManager* _manager)
{
    m_pBattleManager = _manager;
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleMoveMentEnd::~BattleMoveMentEnd()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleMoveMentEnd::Init()
{
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
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
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleMoveMentEnd::Draw()
{
    printfDx("全キャラ行動完了待機処理\n");
    printfDx("%s:%d", m_pBattleManager->m_pAttackNowCharacter->GetName().c_str(), m_pBattleManager->m_pAttackNowCharacter->GetAttackNowFlag());
    DrawFormatString(650, 800, GetColor(255, 255, 255), "%sが%dのこうげき", m_pBattleManager->m_pAttackNowCharacter->GetName().c_str(), m_pBattleManager->m_pAttackNowCharacter->GetAllStatus().ATK);
}
