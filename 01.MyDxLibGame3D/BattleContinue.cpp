//-----------------------------------------------------------------------------
// @brief  ターン継続処理クラス.
//-----------------------------------------------------------------------------
#include "BattleContinue.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleContinue::BattleContinue()
{
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleContinue::~BattleContinue()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleContinue::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_BattleState BattleContinue::Update()
{
    // 全員のアクションが終わるまで行動実行処理へ戻る
    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        if (!m_pCharacter[i]->GetActionFlag())
        {
            return TAG_BattleState::MoveMentStart;
        }
    }

    // 全ての行動処理が完了しており敵も生きているためコマンド処理へ戻る前に行動フラグをfalseに戻す
    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        m_pCharacter[i]->ActionInit();
    }
    return TAG_BattleState::Command;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleContinue::Draw()
{
    printfDx("バトル継続判定処理");
}
