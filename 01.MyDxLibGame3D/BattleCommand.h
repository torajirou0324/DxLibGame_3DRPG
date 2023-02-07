//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand();					// コンストラクタ.
	~BattleCommand() override;			// デストラクタ.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// 初期化処理.
	TAG_BattleState Update() override;	// 更新処理.
	void Draw() override;				// 描画処理.

private:
	void CommandSelectProcess();		// バトルイベントのコマンド選択処理.

	int m_commandIndex;
	int m_enemyAllNum;		// 敵の総数.
	int m_commandWindow[2];	// コマンド選択時の黒枠と白枠.
	int m_arrowPosY;		// 矢印のY座標.
	int m_arrowMoveNum;		// コマンド選択矢印の微動させる用変数.
	int m_intervalNum;

	bool m_escapeFlag;		// コマンド逃げるを押したか判定用
	bool m_selectFlag;		// コマンド選択済か判定用.
	bool m_colorFlag[4];	// コマンド用画像の白黒判定用配列.

	std::string m_commandName[4];	// コマンドに表示する文字.
};