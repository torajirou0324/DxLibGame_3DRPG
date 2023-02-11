//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"
#include "CommandInvoker.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand(class PlayScene* _playScene);		// コンストラクタ.
	~BattleCommand() override;						// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	bool m_escapeFlag;		// コマンド逃げるを押したか判定用.
	bool m_battleFlag;		// コマンドたたかうを押したか判定用.

	TAG_Command m_commandState;
	std::vector<CommandInvoker*> m_pInvokerArray;
};