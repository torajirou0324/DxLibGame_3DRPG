//-----------------------------------------------------------------------------
// @brief  バトルステートの基底クラス.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include <DxLib.h>
#include "Character.h"
#include "ArrowSymbol.h"

enum TAG_BattleState	// バトルイベントの状態管理.
{
	Start,				// 開始処理.
	CommandProcess,		// コマンド選択処理.
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
	virtual ~BattleStateMachine() 
	{
	}

	virtual void Init() = 0;
	virtual void Init(class Player* _player, std::vector<class Enemy*> _enemyArray){}
	virtual TAG_BattleState Update() = 0;
	virtual void Draw() = 0;

protected:
	class PlayScene* m_pPlaySceneStorage;		// 攻撃中のキャラクター
};