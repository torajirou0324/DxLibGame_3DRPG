//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand(class PlayScene* _playScene);					// コンストラクタ.
	~BattleCommand() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	bool m_escapeFlag;		// コマンド逃げるを押したか判定用
	bool m_selectFlag;		// コマンド選択済か判定用.

	std::vector<class CommandInvoker*> m_pInvokerArray;
};