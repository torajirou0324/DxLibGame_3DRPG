#pragma once
#include "BattleStateMachine.h"

class BattleDefeat : public BattleStateMachine
{
public:
	BattleDefeat(class BattleEventManager* _manager);						// コンストラクタ.
	~BattleDefeat() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	class BattleEventManager* m_pBattleManager;
};