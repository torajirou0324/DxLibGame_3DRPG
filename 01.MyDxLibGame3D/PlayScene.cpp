//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#include "PlayScene.h"

#include <functional>
#include <DxLib.h>
#include "Input.h"
#include "Field.h"
#include "ColliderManager.h"
#include "Deamon.h"
#include "WalkAroundEnemy.h"


//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
PlayScene::PlayScene()
	: m_selectFlag(false)
	, m_movieFlag(false)
	, m_battleFlag(false)
	, m_pBattleManager(nullptr)
{
	ColliderManager::CreateInstance();

	// プレイヤー生成
	m_pPlayer = new Player;
	m_pPlayer->Init();

	// ノーマルイベントマネージャーの初期化
	m_pNomalManager = new NormalEventManager(m_pPlayer, std::bind(&PlayScene::ChangeSetBattleEnemyCreate, this, std::placeholders::_1, std::placeholders::_2));
	m_pNomalManager->Init();

	// バトルマネージャーの初期化
	m_pBattleManager = new BattleEventManager(m_pPlayer, m_pEnemyArray, std::bind(&PlayScene::ChangeSetBattleFlag, this, std::placeholders::_1));
	m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);
	
	// カメラのポジションセット
	m_cameraPos = VGet(0.0f, 60.0f, -50.0f);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	if (m_pBattleManager != nullptr)
	{
		delete m_pBattleManager;
		m_pBattleManager = nullptr;
	}
	if (m_pNomalManager != nullptr)
	{
		delete m_pNomalManager;
		m_pNomalManager = nullptr;
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
		// バトルカメラをセット
		SetCameraPositionAndTarget_UpVecY(m_cameraPos, VGet(0.0f, 20.0f, 20.0f));
		m_pBattleManager->Update();
	}
	else
	{
		m_pNomalManager->Update();
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
		m_pBattleManager->Draw();
	}
	else
	{
		m_pNomalManager->Draw();
	}
}

void PlayScene::ChangeSetBattleFlag(const bool& _flag)
{
	m_battleFlag = _flag;

	m_pNomalManager->Init();
}

void PlayScene::ChangeSetBattleEnemyCreate(const bool& _flag, WalkAroundEnemy* _enemy)
{
	m_battleFlag = _flag;

	// 一度前の敵を解放.
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		if (m_pEnemyArray[i] != nullptr)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
	}
	m_pEnemyArray.clear();

	// 敵の生成処理.
	auto CreateLevel = _enemy->GetLevel();
	auto CreateNum = _enemy->GetEnemyNum();

	for (int i = 0; i < CreateNum; i++)
	{
		auto obj = new Deamon;
		obj->Init("デーモン", CreateLevel, VGet(0.0f + (i * 10.0f), 1.0f, 10.0f));
		obj->SetAttackObjectAddress(m_pPlayer);
		m_pEnemyArray.push_back(obj);
	}

	m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);
}