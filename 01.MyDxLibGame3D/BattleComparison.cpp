//-----------------------------------------------------------------------------
// @brief  バトルイベントの素早さ比較処理クラス.
//-----------------------------------------------------------------------------
#include "BattleComparison.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleComparison::BattleComparison(class PlayScene* _playScene)
{
    m_pPlaySceneStorage = _playScene;
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
void BattleComparison::Init()
{
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_BattleState BattleComparison::Update()
{
    auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
    for (int i = 0; i < CharacterALL.size(); i++)
    {
        for (int j = 0; j < CharacterALL.size(); j++)
        {
            if (i == j)
            {

            }
            else
            {
                if (CharacterALL[i]->GetAllStatus().AGL > CharacterALL[j]->GetAllStatus().AGL)
                {
                    if (i < j)
                    {

                    }
                    else
                    {
                        auto tmp = CharacterALL[i];
                        CharacterALL[i] = CharacterALL[j];
                        CharacterALL[j] = tmp;
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
