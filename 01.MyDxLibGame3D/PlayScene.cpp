//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#include "PlayScene.h"

#include <functional>
#include <DxLib.h>
#include "Deamon.h"
#include "Field.h"
#include "Input.h"
#include "ColliderManager.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
PlayScene::PlayScene()
	: m_enemyLevelMax(2)
	, m_enemyLevelMin(1)
	, m_selectFlag(false)
	, m_movieFlag(false)
	, m_battleFlag(false)
	, m_commandIndex(1)
	, m_pBattleManager(nullptr)
{
	ColliderManager::CreateInstance();

	// 壁を生成
	m_pWallCollider = new WallCollider;
	float start = -150.0f;
	float end = 150.0f;
	m_pWallCollider->Init(VGet(start, 0.0f, end), VGet(end, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(m_pWallCollider);

	m_pWallCollider = new WallCollider;
	m_pWallCollider->Init(VGet(start, 0.0f, start), VGet(start, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(m_pWallCollider);

	m_pWallCollider = new WallCollider;
	m_pWallCollider->Init(VGet(start, 0.0f, start), VGet(end, 0.0f, start), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(m_pWallCollider);

	m_pWallCollider = new WallCollider;
	m_pWallCollider->Init(VGet(end, 0.0f, start), VGet(end, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(m_pWallCollider);

	// 自機と敵の生成
	m_pCharacterAttackNow = nullptr;
	m_pPlayer = new Player;
	m_pPlayer->Init();

	auto obj = new Deamon;
	obj->Init("デーモン1", 1, VGet(0.0f, 4.5f, 20.0f));
	obj->SetAttackObjectAddress(m_pPlayer);
	m_pEnemyArray.push_back(obj);
	m_pCharacter.push_back(m_pPlayer);
	m_pCharacter.push_back(obj);

	// バトルステートの初期化
	m_pBattleManager = new BattleEventManager(this);
	m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);

	m_normalState = Round1;
	
	// カメラのポジションセット
	m_cameraPos = VGet(0.0f, 60.0f, -50.0f);

	m_blackWindow = AssetManager::UseImage(AssetManager::BlackWindow);
	m_statusWindow = AssetManager::UseImage(AssetManager::StatusWindow);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	ColliderManager::DeleteInstance();
	if (m_pBattleManager != nullptr)
	{
		delete m_pBattleManager;
		m_pBattleManager = nullptr;
	}
	if (m_pWallCollider != nullptr)
	{
		delete m_pWallCollider;
		m_pWallCollider = nullptr;
	}

	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		if (m_pEnemyArray[i] != nullptr)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
	}
	m_pEnemyArray.clear();
	delete m_pPlayer;
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_SCENE PlayScene::Update()
{
	if (m_battleFlag)
	{
		BattleEvent();
	}
	else
	{
		NormalEvent();
	}

	if (m_battleFlag == false && m_pPlayer->GetDeathFlag())
	{
		return TAG_SCENE::TAG_TITLE;
	}
	return TAG_SCENE::TAG_NONE;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void PlayScene::Draw()
{
	// デバッグ用文字列＋変数値描画
	printfDx("PlayScene\n");

	if (m_battleFlag)
	{
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			m_pEnemyArray[i]->Draw();
		}
		BattleEventDraw();
	}
	else
	{
		NormalEventDraw();
	}
}

//-----------------------------------------------------------------------------
// @brief  敵の生成処理.
//-----------------------------------------------------------------------------
void PlayScene::EnemyCreate(NormalState num)
{
	VECTOR enemySetPosition = VGet(0.0f, 4.5f, 10.0f);	// セットするエネミーのポジション

	// 敵を生成
	for (int i = 0; i < num + 1; i++)
	{
		int level = 0;	// 敵のレベル格納用
		// 敵のレベルを乱数で生成
		if (num == Round1)
		{
			level = GetRand(m_enemyLevelMax - 1) + m_enemyLevelMin;
		}	// 弱いのがでやすい
		if (num == Round2)
		{
			level = GetRand(m_enemyLevelMax) + m_enemyLevelMin; enemySetPosition.x = 20.0f + (-40.0f * i);
		}	// 敵の位置調整+同程度がでやすい
		if (num == Round3)
		{
			level = GetRand(m_enemyLevelMax + 1) + m_enemyLevelMin; enemySetPosition.x = 30.0f + (-30.0f * i);
		}// 敵の位置調整+強いのがでやすい
		if (num == Boss)
		{
			level = 15; enemySetPosition.x = 30.0f + (-30.0f * i);
		}

		// 敵を生成
		if (i < Boss)
		{
			auto obj = new Deamon;
			obj->Init(obj->GetName() + std::to_string(i + 1), level, enemySetPosition);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
	}
	m_battleFlag = true;	// 戦闘開始
}

//-----------------------------------------------------------------------------
// @brief  ノーマルイベントの処理.
//-----------------------------------------------------------------------------
void PlayScene::NormalEvent()
{
	// ムービー作り
	m_pPlayer->Update();

	if (Input::IsPress(ENTER))
	{
		// 敵の要素を削除
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
		m_pEnemyArray.clear();
		m_pCharacter.clear();
		m_pCharacter.push_back(m_pPlayer);
		// 敵生成
		EnemyCreate(m_normalState);
		for (auto& it:m_pEnemyArray)
		{
			m_pCharacter.push_back(it);
		}
		m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);
	}
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの処理.
//-----------------------------------------------------------------------------
void PlayScene::BattleEvent()
{
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, VGet(0.0f, 20.0f, 20.0f));

	m_pPlayer->Animation();
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		m_pEnemyArray[i]->Update();
	}

	m_pBattleManager->Update();
}

//-----------------------------------------------------------------------------
// @brief  ノーマルイベントの描画処理.
//-----------------------------------------------------------------------------
void PlayScene::NormalEventDraw()
{
	printfDx("camPos x:%d y:%d z:%d\n", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);
	Field::DrawCall();
	ColliderManager::ColliderVisuale();
	m_pPlayer->Draw();
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの描画処理.
//-----------------------------------------------------------------------------
void PlayScene::BattleEventDraw()
{
	Field::BattleDrawCall();

	auto white = GetColor(255, 255, 255);	// 白
	auto black = GetColor(0, 0, 0);			// 黒

	DrawGraph(600, 750, m_blackWindow, TRUE);					// 吹き出しウィンドウの表示

	SetFontSize(30);
	// プレイヤーのステータス表示+黒枠
	{
		DrawGraph(0, 750, m_statusWindow, TRUE);
		auto& playerStatus = m_pPlayer->GetAllStatus();
		DrawFormatString(50, 786, GetColor(255, 255, 255), "Lv.%d　　　キツキ　イチカ", playerStatus.LV);

		float berdif = static_cast<float>(playerStatus.EXP) / m_pPlayer->GetEXPMAX();
		auto ber = 270 * berdif;
		DrawBox(50, 840, 50 + ber, 860, GetColor(0, 255, 255), TRUE);
		DrawBox(48, 838, 322, 862, GetColor(255, 255, 255), FALSE);
		
		berdif = static_cast<float>(playerStatus.HP) / m_pPlayer->GetHPMAX();
		ber = 350 * berdif;
		DrawBox(50, 870, 50 + ber, 910, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 868, 402, 912, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 880, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, m_pPlayer->GetHPMAX());

		berdif = static_cast<float>(playerStatus.MP) / m_pPlayer->GetMPMAX();
		ber = 350 * berdif;
		DrawBox(50, 920, 50 + ber, 960, GetColor(0, 100, 200), TRUE);
		DrawBox(48, 918, 402, 962, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 927, GetColor(255, 255, 255), "%d/%d", playerStatus.MP, m_pPlayer->GetMPMAX());
	}

	// エネミーのステータス表示+黒枠
	{
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			int addNum = i + 1;
			DrawGraph(1920 - (520 * addNum), 0, m_statusWindow, TRUE);
			auto& enemyStatus = m_pEnemyArray[i]->GetAllStatus();
			float HPberdif = static_cast<float>(enemyStatus.HP) / m_pEnemyArray[i]->GetHPMAX();
			auto HPber = 350 * HPberdif;

			DrawFormatString(1920 - (520 * addNum) + 50, 36, GetColor(255, 255, 255), "Lv.%d　　%s", enemyStatus.LV, m_pEnemyArray[i]->GetName().c_str());
			DrawBox(1920 - (520 * addNum) + 50, 140, (1920 - (520 * addNum) + 50) + HPber, 180, GetColor(0, 255, 0), TRUE);
			DrawBox(1918 - (520 * addNum) + 50, 138, (1920 - (520 * addNum) + 50) + 352, 182, GetColor(255, 255, 255), FALSE);
			DrawFormatString(1920 - (520 * addNum) + 300, 150, GetColor(255, 255, 255), "%d/%d", enemyStatus.HP, m_pEnemyArray[i]->GetHPMAX());
		}
	}

	m_pBattleManager->Draw();
}
