#pragma once
#include "BattleStateMachine.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand();					// コンストラクタ.
	~BattleCommand() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.
};