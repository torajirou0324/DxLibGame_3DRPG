#pragma once
#include "BattleStateMachine.h"

class BattleDefeat : public BattleStateMachine
{
public:
	BattleDefeat();						// コンストラクタ.
	~BattleDefeat() override;			// デストラクタ.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.
};