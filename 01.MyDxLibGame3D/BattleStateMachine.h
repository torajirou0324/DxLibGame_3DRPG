//-----------------------------------------------------------------------------
// @brief  バトルステートの基底クラス.
//-----------------------------------------------------------------------------
#pragma once
#include <DxLib.h>
#include <string>
#include "Character.h"

enum TAG_BattleState	// バトルイベントの状態管理.
{
	Start,				// 開始処理.
	Command,			// コマンド選択処理.
	Comparison,			// 比較処理.（素早さ）
	MoveMentStart,		// 全キャラ行動処理.
	MoveMentEnd,		// 全キャラ行動完了待機処理.
	BattleEscapeProcess,// 逃げる処理.
	Victory,			// 勝利処理.
	Defeat,				// 敗北処理.
	Continue,			// ターン継続処理.
	None				// 最後.
};

class BattleStateMachine
{
public:
	BattleStateMachine() {}
	virtual ~BattleStateMachine() {}

	virtual void Init(std::vector<Character*>& character, Character*& attackNowCharacter, class PlayScene* playScene) = 0;
	virtual TAG_BattleState Update() = 0;
	virtual void Draw() = 0;

protected:
	std::vector<Character*> m_pCharacter;	// 戦闘中のキャラクターの配列
	Character* m_pCharacterAttackNow;
	class PlayScene* m_pPlayScene;		// 攻撃中のキャラクター
};