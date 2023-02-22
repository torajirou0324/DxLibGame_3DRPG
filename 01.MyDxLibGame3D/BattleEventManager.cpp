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

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleEventManager::BattleEventManager(class PlayScene* scene)
{
	// バトルステートの初期化
	m_battleState = TAG_BattleState::Start;
	m_pBattleStateArray.push_back(new BattleStart(scene));
	m_pBattleStateArray.push_back(new BattleCommand(scene));
	m_pBattleStateArray.push_back(new BattleComparison(scene));
	m_pBattleStateArray.push_back(new BattleMoveMentStart(scene));
	m_pBattleStateArray.push_back(new BattleMoveMentEnd(scene));
	m_pBattleStateArray.push_back(new BattleEscape(scene));
	m_pBattleStateArray.push_back(new BattleVictory(scene));
	m_pBattleStateArray.push_back(new BattleDefeat(scene));
	m_pBattleStateArray.push_back(new BattleContinue(scene));
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleEventManager::~BattleEventManager()
{
	for (const auto it : m_pBattleStateArray)
	{
		delete it;
	}
	m_pBattleStateArray.clear();
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleEventManager::Init()
{

}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void BattleEventManager::Update()
{
	auto tag = m_pBattleStateArray[m_battleState]->Update();

	if (tag != TAG_BattleState::None)
	{
		m_battleState = tag;
		m_pBattleStateArray[tag]->Init();
	}
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleEventManager::Draw()
{
	m_pBattleStateArray[m_battleState]->Draw();
}
