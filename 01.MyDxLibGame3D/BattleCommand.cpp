//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理クラス.
//-----------------------------------------------------------------------------
#include "BattleCommand.h"
#include "Input.h"
#include "CommandInvoker.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleCommand::BattleCommand(class PlayScene* _playScene)
	: m_selectFlag(false)
	, m_escapeFlag(false)
{
	m_pPlaySceneStorage = _playScene;
	//std::function<void(MoveCommand)> func = 
	m_pInvokerArray.push_back(new CommandInvoker("こうげき"));
	//m_pInvokerArray[TAG_Command::AttackCommand]->SetOnCommand(new SimpleCommand())
	m_pInvokerArray.push_back(new CommandInvoker("まほう"));
	m_pInvokerArray.push_back(new CommandInvoker("もちもの"));
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleCommand::~BattleCommand()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleCommand::Init()
{
	m_selectFlag = false;
	m_escapeFlag = false;
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_BattleState BattleCommand::Update()
{
	// 逃げるコマンドが選択されたためESCAPE処理へ
	if (m_escapeFlag)
	{
		return TAG_BattleState::BattleEscapeProcess;
	}
	// 戦闘コマンドが選択されたため素早さ比較処理へ
    if (m_selectFlag)
    {
        return TAG_BattleState::Comparison;
    }

    return TAG_BattleState::None;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleCommand::Draw()
{
	DrawFormatString(650, 800, GetColor(255, 255, 255), "コマンド選択中...");

	SetFontSize(60);


	//DrawArrowSide(1370, m_arrowPosY); // 矢印の表示
	//DrawGraph(m_arrowPosX + m_arrowMoveNum, m_arrowPosY, m_arrowHandle[m_textFlag], TRUE);
}
