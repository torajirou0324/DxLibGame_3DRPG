//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"
#include "Enemy.h"
#include "Player.h"
#include "NormalEventManager.h"
#include "BattleEventManager.h"

class PlayScene : public Scene
{
public:
	PlayScene();					// コンストラクタ.
	~PlayScene() override;			// デストラクタ.

	TAG_SCENE Update() override;	// 更新処理.
	void Draw() override;			// 描画処理.

	// バトルフラグをセットする
	void ChangeSetBattleFlag(const bool& _flag);
	void ChangeSetBattleEnemyCreate(const bool& _flag, class WalkAroundEnemy* _enemy);
private:
	Player* m_pPlayer;
	std::vector<Enemy*> m_pEnemyArray;

	NormalEventManager* m_pNomalManager;	// ノーマルイベント管理クラスポインタ.
	BattleEventManager* m_pBattleManager;	// バトルイベント管理クラスポインタ.

	bool m_selectFlag;
	bool m_movieFlag;
	bool m_battleFlag;

	VECTOR m_cameraPos;
};