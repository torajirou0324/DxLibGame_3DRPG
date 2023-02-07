//-----------------------------------------------------------------------------
// @brief  全キャラ行動処理実行クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleMoveMentStart : public BattleStateMachine
{
public:
	BattleMoveMentStart();						// コンストラクタ.
	~BattleMoveMentStart() override;			// デストラクタ.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	bool m_enemyAllDeadFlag;			// 敵が死んでいるか判定用.
	bool m_playerDeadFlag;				// 自機が死んでいるか判定用.
};