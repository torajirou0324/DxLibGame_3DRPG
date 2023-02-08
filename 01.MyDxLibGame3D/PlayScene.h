//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"
#include "BattleStateMachine.h"
#include "Enemy.h"
#include "Player.h"

enum NormalState		// ノーマルイベントの状態管理.
{
	Round1,		// 1バトル目.
	Round2,		// 2バトル目.
	Round3,		// 3バトル目.
	Boss,		// ボス戦.
	End
};

class PlayScene : public Scene
{
public:
	PlayScene();					// コンストラクタ.
	~PlayScene() override;			// デストラクタ.

	TAG_SCENE Update() override;	// 更新処理.
	void Draw() override;			// 描画処理.

	// 現在攻撃しているキャラクターをバトルステートマシンクラスから受け取る用
	void SetAttackObjectAddress(Character* _AttackObject) { m_pCharacterAttackNow = _AttackObject; }
	// バトルフラグをセットする
	void SetBattleFlag(const bool& _flag) { m_battleFlag = _flag; }
	// ノーマルステートをセットする
	void SetNomalState(const NormalState& _normalState) { m_normalState = _normalState; }
	// ノーマルステートをゲットする
	const NormalState& GetNomalState() const { return m_normalState; }
private:

	void BattleStateSwitching(const TAG_BattleState battleState);

	void EnemyCreate(NormalState num);		// 敵生成処理.
	void NormalEvent();		// ノーマルイベント.
	void BattleEvent();		// 戦闘イベント.
	void NormalEventDraw();	// ノーマルイベント描画処理.
	void BattleEventDraw(); // 戦闘イベント描画処理.

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
	int m_enemyLevelMin;	// エンカウントする敵の最小レベル保存用.
	int gaussianScreen;		// 画面ぼかし用画像格納用ハンドル.

	int m_waitTimer;		// 待機時間保存用変数.

	bool m_textFlag;
	bool m_selectFlag;
	bool m_movieFlag;
	bool m_battleFlag;
	bool m_enemyDeadFlag;
	bool m_healFlag;		// 一時的な回復判定用.
	std::vector<bool> m_colorFlag;
	std::vector<std::string> m_commandName;
	std::vector<Character*> m_pCharacter;
	std::vector<Enemy*> m_pEnemyArray;
	Character* m_pCharacterAttackNow;		// 攻撃中のキャラクター
	Player* m_pPlayer;

	BattleStateMachine* m_pBattleState;				// 現在のバトル状態
	BattleStateMachine* m_pBattleStateArray[9];		// バトルの状態クラスを全て格納した配列

	NormalState m_normalState;				// ノーマルイベントの状態管理.

	VECTOR m_cameraPos;
};