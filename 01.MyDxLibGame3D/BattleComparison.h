#pragma once
#include "BattleStateMachine.h"

class BattleComparison : public BattleStateMachine
{
public:
	BattleComparison();						// コンストラクタ.
	~BattleComparison() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.
};