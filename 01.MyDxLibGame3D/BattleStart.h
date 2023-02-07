#pragma once
#include "BattleStateMachine.h"

class BattleStart : public BattleStateMachine
{
public:
	BattleStart();						// コンストラクタ.
	~BattleStart() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.
};