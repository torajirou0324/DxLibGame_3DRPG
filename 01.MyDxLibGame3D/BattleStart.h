//-----------------------------------------------------------------------------
// @brief  バトルイベントの戦闘開始処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleStart : public BattleStateMachine
{
public:
	BattleStart(class PlayScene* _playScene);						// コンストラクタ.
	~BattleStart() override;			// デストラクタ.

	void Init() override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	int m_waitTimer;		// 画面ぼかし時間計り用.
	int gaussianScreen;		// 画面ぼかし用画像格納用ハンドル.
};