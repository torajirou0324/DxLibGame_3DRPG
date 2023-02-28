//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"
#include "BattleCommandManager.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand(class BattleEventManager* _manager);		// コンストラクタ.
	~BattleCommand() override;						// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	std::vector<BattleCommandManager*> m_pCommandManager;
	TAG_CommandState m_commandState;

	class BattleEventManager* m_pBattleManager;
};