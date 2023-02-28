//-----------------------------------------------------------------------------
// @brief  バトルイベント管理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleEventManager
{
public:
	BattleEventManager(Player* _player, std::vector<Enemy*> _enemyArray, std::function<void(bool)> _func);
	~BattleEventManager();

	void Init(Player* _player, std::vector<Enemy*> _enemyArray);
	void Update();
	void Draw();
	
	std::function<void(bool)> m_func;
	Player* m_pPlayer;
	std::vector<Enemy*> m_pEnemyArray;
	std::vector<Character*> m_pCharacterArray;
	Character* m_pAttackNowCharacter;
private:
	std::vector<BattleStateMachine*> m_pBattleStateArray;	// バトルの状態クラスを全て格納した配列
	TAG_BattleState m_battleState;							// 現在のバトル状態
};