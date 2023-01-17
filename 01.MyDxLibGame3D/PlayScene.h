//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#pragma once
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

	int m_blackWindow;		// コマンド選択時の黒枠.
	int m_statusWindow;		// レベル・経験値量・体力量を映す用の黒枠.
	int m_arrowHandle;		// コマンド選択矢印のモデルハンドル.
	int m_arrowPosX;		// コマンド選択矢印のX座標.
	int m_arrowPosY;		// コマンド選択矢印のY座標.
	int m_randomNumber;		// 乱数格納用の変数.
	int m_EncountInterval;	// 敵とのエンカウント間隔判定用の変数.
	int m_commandIndex;		// コマンド選択遷移の判定用変数.

	int m_playerHPMAX;
	int m_enemyHPMAX;
	class Enemy* m_pEnemy;
};