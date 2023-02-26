//-----------------------------------------------------------------------------
// @brief  全キャラ行動完了待機処理クラス.
//-----------------------------------------------------------------------------
#include "BattleMoveMentEnd.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleMoveMentEnd::BattleMoveMentEnd(class PlayScene* _playScene)
{
    m_pPlaySceneStorage = _playScene;
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
    if (!m_pPlaySceneStorage->GetAttackNowCharacter()->GetAttackNowFlag())
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
    printfDx("%s:%d", m_pPlaySceneStorage->GetAttackNowCharacter()->GetName().c_str(), m_pPlaySceneStorage->GetAttackNowCharacter()->GetAttackNowFlag());
    DrawFormatString(650, 800, GetColor(255, 255, 255), "%sが%dのこうげき", m_pPlaySceneStorage->GetAttackNowCharacter()->GetName().c_str(), m_pPlaySceneStorage->GetAttackNowCharacter()->GetAllStatus().ATK);
}
