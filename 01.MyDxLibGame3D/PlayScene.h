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

	std::vector<Character*> GetCharacterArrayAddress() { return m_pCharacter; }
	Character* GetAttackNowCharacter() { return m_pCharacterAttackNow; }
	Player* GetPlayerAddress() { return m_pPlayer; }
private:

	void EnemyCreate(NormalState num);		// 敵生成処理.
	void NormalEvent();		// ノーマルイベント.
	void BattleEvent();		// 戦闘イベント.
	void NormalEventDraw();	// ノーマルイベント描画処理.
	void BattleEventDraw(); // 戦闘イベント描画処理.

	int m_blackWindow;		// 行動後の結果文字描画用の黒枠.
	int m_statusWindow;		// レベル・経験値量・体力量を映す用の黒枠.
	int m_commandIndex;		// コマンド選択遷移の判定用変数.
	int m_enemyLevelMax;	// エンカウントする敵の最大レベル保存用.
	int m_enemyLevelMin;	// エンカウントする敵の最小レベル保存用.

	bool m_selectFlag;
	bool m_movieFlag;
	bool m_battleFlag;
	std::vector<Character*> m_pCharacter;
	std::vector<Enemy*> m_pEnemyArray;
	Character* m_pCharacterAttackNow;		// 攻撃中のキャラクター
	Player* m_pPlayer;

	TAG_BattleState m_battleState;													// 現在のバトル状態
	std::unordered_map<TAG_BattleState, BattleStateMachine*> m_pBattleStateArray;	// バトルの状態クラスを全て格納した配列

	NormalState m_normalState;				// ノーマルイベントの状態管理.

	VECTOR m_cameraPos;
};