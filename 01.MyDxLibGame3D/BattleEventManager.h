//-----------------------------------------------------------------------------
// @brief  バトルイベント管理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleEventManager
{
public:
	BattleEventManager(class PlayScene* scene);
	~BattleEventManager();

	void Update();
	void Draw();

private:
	std::vector<BattleStateMachine*> m_pBattleState;	// バトルの状態クラスを全て格納した配列
	TAG_BattleState m_battleState;						// 現在のバトル状態
};