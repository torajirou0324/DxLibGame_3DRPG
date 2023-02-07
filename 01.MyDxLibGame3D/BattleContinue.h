//-----------------------------------------------------------------------------
// @brief  ターン継続処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleContinue : public BattleStateMachine
{
public:
	BattleContinue();					// コンストラクタ.
	~BattleContinue() override;			// デストラクタ.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.
};