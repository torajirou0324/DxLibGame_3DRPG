//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理クラス.
//-----------------------------------------------------------------------------
#include "BattleCommand.h"
#include "Input.h"
#include "Enemy.h"
#include "ArrowSymbol.h"
#include "SimpleCommand.h"
#include "SkillCommand.h"
#include "TargetCommand.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleCommand::BattleCommand(class PlayScene* _playScene)
	: m_commandState(TAG_CommandState::TAG_isPlay)
{
	auto player = _playScene->GetPlayerAddress();
	std::function<void(SKILL)> skillfunc = std::bind(&Player::SetUseSkill, player, std::placeholders::_1);
	std::function<void(Character*)> targetObjectfunc = std::bind(&Player::SetAttackObjectAddress, player, std::placeholders::_1);
	// コマンド選択の遷移必要数生成
	for (int i = 0; i < TAG_CommandState::TAG_Max; i++)
	{
		m_pCommandManager.push_back(new BattleCommandManager);
	}
	// 戦闘にするかしないか選択用クラス生成
	m_pCommandManager[TAG_CommandState::TAG_isPlay]->SetCommand(new SimpleCommand("にげる", TAG_CommandState::TAG_Escape, TAG_CommandState::TAG_None));
	m_pCommandManager[TAG_CommandState::TAG_isPlay]->SetCommand(new SimpleCommand("たたかう", TAG_CommandState::TAG_isMoveType, TAG_CommandState::TAG_None));
	// 行動のタイプ（まほうを使うか純粋にこうげきをするか）
	m_pCommandManager[TAG_CommandState::TAG_isMoveType]->SetCommand(new SimpleCommand("まほう", TAG_CommandState::TAG_isMagicSkill, TAG_CommandState::TAG_isPlay));
	m_pCommandManager[TAG_CommandState::TAG_isMoveType]->SetCommand(new SimpleCommand("こうげき",TAG_CommandState::TAG_isAttackSkill, TAG_CommandState::TAG_isPlay));
	// 攻撃格納用
	for (int i = 0; i < 4; i++)
	{
		m_pCommandManager[TAG_CommandState::TAG_isAttackSkill]->SetCommand(new SkillCommand(skillfunc,TAG_CommandState::TAG_isTargetAttack, TAG_CommandState::TAG_isMoveType));
		m_pCommandManager[TAG_CommandState::TAG_isMagicSkill]->SetCommand(new SkillCommand(skillfunc, TAG_CommandState::TAG_isTargetAttack, TAG_CommandState::TAG_isMoveType));
		m_pCommandManager[TAG_CommandState::TAG_isTargetAttack]->SetCommand(new TargetCommand(targetObjectfunc, TAG_CommandState::TAG_ActionCompleted, TAG_CommandState::TAG_isMoveType));
	}
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleCommand::~BattleCommand()
{
	for (int i = 0; i < TAG_CommandState::TAG_Max; i++)
	{
		delete m_pCommandManager[i];
		m_pCommandManager[i] = nullptr;
	}
	m_pCommandManager.clear();
}

//-----------------------------------------------------------------------------
// @brief  ターン毎の初期化処理.
//-----------------------------------------------------------------------------
void BattleCommand::Init()
{
	m_commandState = TAG_CommandState::TAG_isPlay;
	for (int i = 0; i < TAG_CommandState::TAG_Max; i++)
	{
		m_pCommandManager[i]->Init();
	}
}

//-----------------------------------------------------------------------------
// @brief  バトル開始時のみ初期化処理.
//-----------------------------------------------------------------------------
void BattleCommand::Init(class Player* _player, std::vector<class Enemy*> _enemyArray)
{
	auto skill = _player->GetSKILL();
	m_pCommandManager[TAG_CommandState::TAG_isAttackSkill]->Init(skill);
	m_pCommandManager[TAG_CommandState::TAG_isMagicSkill]->Init(skill);
	m_pCommandManager[TAG_CommandState::TAG_isTargetAttack]->Init(_enemyArray);
	
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_BattleState BattleCommand::Update()
{
	auto tag = m_pCommandManager[m_commandState]->Update();
	
	if (tag != TAG_CommandState::TAG_None)
	{
		m_commandState = tag;
	}

	// 逃げるコマンドが選択されたためESCAPE処理へ
	if (tag == TAG_CommandState::TAG_Escape)
	{
		return TAG_BattleState::BattleEscapeProcess;
	}
	// 戦闘コマンドが選択されたため素早さ比較処理へ
    if (tag == TAG_CommandState::TAG_ActionCompleted)
    {
		return TAG_BattleState::MoveMentStart;
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
	m_pCommandManager[m_commandState]->Draw();
}
