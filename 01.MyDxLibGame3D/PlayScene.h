//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"
#include "Enemy.h"
#include "Player.h"

class PlayScene : public Scene
{
public:
	PlayScene();					// コンストラクタ.
	~PlayScene() override;			// デストラクタ.

	TAG_SCENE Update() override;	// 更新処理.
	void Draw() override;			// 描画処理.

private:
	void NormalEvent();
	void BattleEvent();		// 戦闘イベント.
	void BattleEventDraw(); // 戦闘イベント描画処理.
	void CommandEvent();	// コマンド選択処理.

	enum NormalState		// ノーマルイベントの状態管理.
	{
		Round1,		// 1バトル目.
		Round2,		// 2バトル目.
		Round3,		// 3バトル目.
		Boss,		// ボス戦.
		End
	};

	enum BattleState		// バトルイベントの状態管理.
	{
		Start,				// 開始処理.
		Command,			// コマンド選択処理.
		Comparison,			// 比較処理.（素早さ）
		MoveMent,			// 行い.
		AttackProcess,		// 攻撃処理.
		SpecialMoveProcess,	// 特殊技処理.
		PersonalEffects,	// もちもの使用処理.
		Victory,			// 勝利処理.
		Defeat,				// 敗北処理.
		Escape,				// 逃げる処理.
		Continue			// ターン継続処理.
	};

	int m_blackWindow;		// 行動後の結果文字描画用の黒枠.
	int m_commandWindow[2];	// コマンド選択時の黒枠と白枠.
	int m_statusWindow;		// レベル・経験値量・体力量を映す用の黒枠.
	int m_arrowHandle[2];	// コマンド選択矢印のモデルハンドル.
	int m_arrowPosX;		// コマンド選択矢印のX座標.
	int m_arrowPosY;		// コマンド選択矢印のY座標.
	int m_arrowMoveNum;		// コマンド選択矢印の微動させる用変数.
	int m_intervalNum;
	int m_commandIndex;		// コマンド選択遷移の判定用変数.
	int m_enemyLevelMax;	// エンカウントする敵の最大レベル保存用.

	int m_waitTimer;		// 待機時間保存用変数.

	bool m_textFlag;
	bool m_battleFlag;
	bool m_enemyDeadFlag;
	std::vector<bool> m_colorFlag;
	std::vector<std::string> m_commandName;
	std::vector<Character*> m_pCharacter;
	std::vector<Enemy*> m_pEnemyArray;
	Character* m_pCharacterAttackNow;		// 攻撃中のキャラクター
	Player* m_pPlayer;

	NormalState m_normalState;				// ノーマルイベントの状態管理.
	BattleState m_battleState;				// バトルイベントの状態管理.
};