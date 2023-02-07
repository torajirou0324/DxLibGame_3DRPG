//-----------------------------------------------------------------------------
// @brief  バトルイベントの戦闘開始処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleStart : public BattleStateMachine
{
public:
	BattleStart();						// コンストラクタ.
	~BattleStart() override;			// デストラクタ.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	int m_waitTimer;		// 画面ぼかし時間計り用.
	int gaussianScreen;		// 画面ぼかし用画像格納用ハンドル.
	int m_arrowMoveNum;		// コマンド選択矢印の微動させる用変数.
	int m_intervalNum;
};