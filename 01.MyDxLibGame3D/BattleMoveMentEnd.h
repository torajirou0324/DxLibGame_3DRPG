//-----------------------------------------------------------------------------
// @brief  全キャラ行動完了待機処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleMoveMentEnd : public BattleStateMachine
{
public:
	BattleMoveMentEnd(class PlayScene* _playScene);					// コンストラクタ.
	~BattleMoveMentEnd() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.
};