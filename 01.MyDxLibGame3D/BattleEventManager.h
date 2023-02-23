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

	void Init(class Player* _player, std::vector<class Enemy*> _enemyArray);
	void Update();
	void Draw();

private:
	std::vector<BattleStateMachine*> m_pBattleStateArray;	// バトルの状態クラスを全て格納した配列
	TAG_BattleState m_battleState;							// 現在のバトル状態
};