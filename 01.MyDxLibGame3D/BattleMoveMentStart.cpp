//-----------------------------------------------------------------------------
// @brief  全キャラ行動処理実行クラス.
//-----------------------------------------------------------------------------
#include "BattleMoveMentStart.h"
#include "Player.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleMoveMentStart::BattleMoveMentStart()
    : m_enemyAllDeadFlag(false)
    , m_playerDeadFlag(false)
{
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleMoveMentStart::~BattleMoveMentStart()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleMoveMentStart::Init()
{
    m_enemyAllDeadFlag = true;
    m_playerDeadFlag = false;
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_BattleState BattleMoveMentStart::Update()
{
    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        // 行動が終わっていないかつ、死んでいないとき行動する
        if (!m_pCharacter[i]->GetActionFlag() && !m_pCharacter[i]->GetDeathFlag())
        {
            m_pCharacter[i]->Action();
            m_pCharacter[i]->Attack();
            m_pPlayScene->SetAttackObjectAddress(m_pCharacter[i]);    // 現在行動しているキャラクターを代入する
            break;
        }
    }

    for (int i = 0; i < m_pCharacter.size(); i++)
    {
        if (!m_pCharacter[i]->GetDeathFlag())
        {
            // 敵が現在死んでいないか
            if (m_pCharacter[i]->GetAllStatus().HP <= 0 && m_pCharacter[i]->GetCharaName() == CharacterName::UnHuman)
            {
                // 死んでいたら死亡フラグを立て、プレイヤーに自身の付与予定経験値を加算する
                m_pCharacter[i]->Dead();
                int EXP = m_pCharacter[i]->GetAllStatus().EXP;
                auto player = dynamic_cast<Player*>(m_pCharacter[0]);
                // キャストが失敗したら抜ける
                if (player == nullptr)
                {
                    break;
                }
                player->EXPAdd(EXP);
            }
            else if(m_pCharacter[i]->GetCharaName() == CharacterName::UnHuman)
            {
                // 敵が1人でも生きているためfalseを代入
                m_enemyAllDeadFlag = false;
            }
            // プレイヤーが死んでいないか
            if (m_pCharacter[i]->GetAllStatus().HP <= 0 && m_pCharacter[i]->GetCharaName() == CharacterName::Human)
            {
                // 死んでいるためフラグを立てる
                m_pCharacter[i]->Dead();
            }
        }
        else
        {
            m_pCharacter[i]->Action();
        }
    }

    // プレイヤーが現在死んでいないか
    if (m_pCharacter[0]->GetDeathFlag())
    {
        // 死んでいるため敗北処理へ
        return TAG_BattleState::Defeat;
    }
    // 敵が全滅していないか
    if (m_enemyAllDeadFlag)
    {
        // 死んでいるため勝利処理へ
        return TAG_BattleState::Victory;
    }

    // 現在の行動中のキャラクター行動完了待機処理へ
    return TAG_BattleState::MoveMentEnd;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleMoveMentStart::Draw()
{
    printfDx("全キャラ行動処理");
}
