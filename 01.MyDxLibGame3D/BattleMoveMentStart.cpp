//-----------------------------------------------------------------------------
// @brief  全キャラ行動処理実行クラス.
//-----------------------------------------------------------------------------
#include "BattleMoveMentStart.h"
#include "Player.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleMoveMentStart::BattleMoveMentStart(class PlayScene* _playScene)
    : m_enemyAllDeadFlag(false)
    , m_playerDeadFlag(false)
{
    m_pPlaySceneStorage = _playScene;
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
    auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
    for (int i = 0; i < CharacterALL.size(); i++)
    {
        // 行動が終わっていないかつ、死んでいないとき行動する
        if (!CharacterALL[i]->GetActionFlag() && !CharacterALL[i]->GetDeathFlag())
        {
            CharacterALL[i]->Action();
            CharacterALL[i]->Attack();
            m_pPlaySceneStorage->SetAttackObjectAddress(CharacterALL[i]);    // 現在行動しているキャラクターを代入する
            break;
        }
    }

    for (int i = 0; i < CharacterALL.size(); i++)
    {
        if (!CharacterALL[i]->GetDeathFlag())
        {
            // 敵が現在死んでいないか
            if (CharacterALL[i]->GetAllStatus().HP <= 0 && !CharacterALL[i]->GetDiscrimination())
            {
                // 死んでいたら死亡フラグを立て、プレイヤーに自身の付与予定経験値を加算する
                CharacterALL[i]->Dead();
                int EXP = CharacterALL[i]->GetAllStatus().EXP;
                auto player = dynamic_cast<Player*>(CharacterALL[0]);
                // キャストが失敗したら抜ける
                if (player == nullptr)
                {
                    break;
                }
                player->EXPAdd(EXP);
            }
            else if(!CharacterALL[i]->GetDiscrimination())
            {
                // 敵が1人でも生きているためfalseを代入
                m_enemyAllDeadFlag = false;
            }
            // プレイヤーが死んでいないか
            if (CharacterALL[i]->GetAllStatus().HP <= 0 && CharacterALL[i]->GetDiscrimination())
            {
                // 死んでいるためフラグを立てる
                CharacterALL[i]->Dead();
            }
        }
        else
        {
            CharacterALL[i]->Action();
        }
    }

    // プレイヤーが現在死んでいないか
    if (CharacterALL[0]->GetDeathFlag())
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
