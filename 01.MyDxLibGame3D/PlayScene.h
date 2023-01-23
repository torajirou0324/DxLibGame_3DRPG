//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"

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

	enum BattleState		// バトルイベントの状態管理.
	{
		Start,				// 開始処理.
		Command,			// コマンド選択処理.
		Comparison,			// 比較処理.（素早さ）
		AttackProcess,		// 攻撃処理.
		SpecialMoveProcess,	// 特殊技処理.
		PersonalEffects,	// もちもの使用処理.
		Victory,			// 勝利処理.
		Defeat,				// 敗北処理.
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

	int m_waitTimer;		// 待機時間保存用変数

	int m_enemyHPMAX;

	bool m_textFlag;
	std::vector<bool> m_colorFlag;
	std::vector<std::string> m_commandName;

	class Enemy* m_pEnemy;

	BattleState m_battleState;// バトルイベントの状態管理.
};