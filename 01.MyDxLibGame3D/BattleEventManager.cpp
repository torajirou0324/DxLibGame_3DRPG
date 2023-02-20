//-----------------------------------------------------------------------------
// @brief  バトルイベント管理クラス.
//-----------------------------------------------------------------------------
#include "BattleEventManager.h"
#include "BattleStart.h"
#include "BattleCommand.h"
#include "BattleComparison.h"
#include "BattleMoveMentStart.h"
#include "BattleMoveMentEnd.h"
#include "BattleEscape.h"
#include "BattleVictory.h"
#include "BattleDefeat.h"
#include "BattleContinue.h"

BattleEventManager::BattleEventManager(class PlayScene* scene)
{
	// バトルステートの初期化
	m_battleState = TAG_BattleState::Start;
	m_pBattleState.push_back(new BattleStart(scene));
	m_pBattleState.push_back(new BattleCommand(scene));
	m_pBattleState.push_back(new BattleComparison(scene));
	m_pBattleState.push_back(new BattleMoveMentStart(scene));
	m_pBattleState.push_back(new BattleMoveMentEnd(scene));
	m_pBattleState.push_back(new BattleEscape(scene));
	m_pBattleState.push_back(new BattleVictory(scene));
	m_pBattleState.push_back(new BattleDefeat(scene));
	m_pBattleState.push_back(new BattleContinue(scene));
}

BattleEventManager::~BattleEventManager()
{
	for (const auto it : m_pBattleState)
	{
		delete it;
	}
	m_pBattleState.clear();
}

void BattleEventManager::Update()
{
	auto tag = m_pBattleState[m_battleState]->Update();

	if (tag != TAG_BattleState::None)
	{
		m_battleState = tag;
	}
}

void BattleEventManager::Draw()
{
	m_pBattleState[m_battleState]->Draw();
}
