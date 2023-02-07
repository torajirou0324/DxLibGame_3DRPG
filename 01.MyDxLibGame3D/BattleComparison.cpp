//-----------------------------------------------------------------------------
// @brief  バトルイベントの素早さ比較処理クラス.
//-----------------------------------------------------------------------------
#include "BattleComparison.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleComparison::BattleComparison()
{
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleComparison::~BattleComparison()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleComparison::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
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
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleComparison::Draw()
{
    printfDx("素早さ比較処理");
}
