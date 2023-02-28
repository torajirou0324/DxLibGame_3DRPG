//-----------------------------------------------------------------------------
// @brief  全キャラ行動処理実行クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleMoveMentStart : public BattleStateMachine
{
public:
	BattleMoveMentStart(class BattleEventManager* _manager);						// コンストラクタ.
	~BattleMoveMentStart() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	bool m_enemyAllDeadFlag;			// 敵が死んでいるか判定用.
	bool m_playerDeadFlag;				// 自機が死んでいるか判定用.

	class BattleEventManager* m_pBattleManager;
};