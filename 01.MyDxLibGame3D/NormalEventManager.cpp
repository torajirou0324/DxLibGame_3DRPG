//-----------------------------------------------------------------------------
// @brief  ノーマルイベント管理クラス.
//-----------------------------------------------------------------------------
#include "NormalEventManager.h"

#include <algorithm>
#include "Input.h"
#include "Field.h"
#include "ColliderManager.h"
#include "Player.h"
#include "Collision.h"
#include "ArrowSymbol.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
NormalEventManager::NormalEventManager(Player* _player, std::function<void(bool, class WalkAroundEnemy*)> _func)
	: m_pPlayer(_player)
	, m_func(_func)
{
	// 徘徊する敵の生成
	auto obj = new WalkAroundEnemy;
	obj->Init(VGet(0.0f, 0.0f, 100.0f), 1, m_pPlayer->GetAllStatus().LV);
	m_pEnemyArray.push_back(obj);
	auto obj2 = new WalkAroundEnemy;
	obj2->Init(VGet(0.0f, 0.0f, 500.0f), 2, m_pPlayer->GetAllStatus().LV);
	m_pEnemyArray.push_back(obj2);

	// 1面の壁を生成
	float start = -150.0f;
	float end = 150.0f;
	auto wall = new WallCollider;
	wall->Init(VGet(start, 0.0f, start), VGet(end, 0.0f, start), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall);
	m_pWallColliderArray.push_back(wall);
	auto wall2 = new WallCollider;
	wall2->Init(VGet(start, 0.0f, start), VGet(start, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall2);
	m_pWallColliderArray.push_back(wall2);
	auto wall3 = new WallCollider;
	wall3->Init(VGet(end, 0.0f, start), VGet(end, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall3);
	m_pWallColliderArray.push_back(wall3);
	auto wall4 = new WallCollider;
	wall4->Init(VGet(start, 0.0f, end), VGet(-50.0f, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall4);
	m_pWallColliderArray.push_back(wall4);
	auto wall5 = new WallCollider;
	wall5->Init(VGet(50.0f, 0.0f, end), VGet(end, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall5);
	m_pWallColliderArray.push_back(wall5);

	// 通路壁
	auto wall6 = new WallCollider;
	wall6->Init(VGet(50.0f, 0.0f, 150.0f), VGet(50.0f, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall6);
	m_pWallColliderArray.push_back(wall6);
	auto wall7 = new WallCollider;
	wall7->Init(VGet(-50.0f, 0.0f, 150.0f), VGet(-50.0f, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall7);
	m_pWallColliderArray.push_back(wall7);

	// 2面の壁を生成
	auto wall8 = new WallCollider;
	wall8->Init(VGet(start, 0.0f, 750.0f), VGet(end, 0.0f, 750.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall8);
	m_pWallColliderArray.push_back(wall8);
	auto wall9 = new WallCollider;
	wall9->Init(VGet(start, 0.0f, 450.0f), VGet(start, 0.0f, 750.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall9);
	m_pWallColliderArray.push_back(wall9);
	auto wall10 = new WallCollider;
	wall10->Init(VGet(end, 0.0f, 450.0f), VGet(end, 0.0f, 750.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall10);
	m_pWallColliderArray.push_back(wall10);
	auto wall11 = new WallCollider;
	wall11->Init(VGet(start, 0.0f, 450.0f), VGet(-50.0f, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall11);
	m_pWallColliderArray.push_back(wall11);
	auto wall12 = new WallCollider;
	wall12->Init(VGet(50.0f, 0.0f, 450.0f), VGet(end, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall12);
	m_pWallColliderArray.push_back(wall12);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
NormalEventManager::~NormalEventManager()
{
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		if (m_pEnemyArray[i] != nullptr)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
	}

	for (int i = 0; i < m_pWallColliderArray.size(); i++)
	{
		if (m_pWallColliderArray[i] != nullptr)
		{
			ColliderManager::RemoveColliderInfo(m_pWallColliderArray[i]);
			delete m_pWallColliderArray[i];
			m_pWallColliderArray[i] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void NormalEventManager::Init()
{
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void NormalEventManager::Update()
{
	// エンカウントしたかのフラグと敵の情報
	bool EncountFlag = false;
	WalkAroundEnemy* enemy = nullptr;

	// キャラクタの更新処理
	m_pPlayer->Update();
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		m_pEnemyArray[i]->Update();
		EncountFlag = m_pEnemyArray[i]->GetIsCollisionPlayerFlag();
		if (EncountFlag)
		{
			// プレイヤーと当たっている敵の情報を代入
			enemy = m_pEnemyArray[i];
			break;
		}
	}

	if (EncountFlag)
	{
		// エンカウントした敵の情報を渡してバトル管理クラスを初期化する.
		m_func(true, enemy);

		// removeは特定の要素以外を有効領域に移動させる
		auto newend = std::remove(m_pEnemyArray.begin(), m_pEnemyArray.end(), enemy);

		// 移動させるだけで削除はしないため
		// 無効領域を削除するにはeraseと併用して使用する
		m_pEnemyArray.erase(newend, m_pEnemyArray.end());

		// 当たった敵を消す
		if (enemy != nullptr)
		{
			delete enemy;
			enemy = nullptr;
		}
	}

	if (Input::IsPress(ENTER))
	{
		if (m_fadeFlag)
		{
			FadeOutInit();
			m_fadeFlag = false;
		}
		else
		{
			FadeInInit();
			m_fadeFlag = true;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void NormalEventManager::Draw()
{
	Field::DrawCall();
	ColliderManager::ColliderVisuale();
	m_pPlayer->Draw();
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		m_pEnemyArray[i]->Draw();
	}

	// 矢印アイコンのアルファ値判定
	if (Input::IsPressed(UP))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(250, 850, 1.0f, 0.0f, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(250, 850, 1.0f, 0.0f, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	if (Input::IsPressed(DOWN))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(250, 1000, 1.0f, CollMath::m_pi, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(250, 1000, 1.0f, CollMath::m_pi, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	if (Input::IsPressed(RIGHT))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(400, 1000, 1.0f, CollMath::m_pi / 2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(400, 1000, 1.0f, CollMath::m_pi / 2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	if (Input::IsPressed(LEFT))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(100, 1000, 1.0f, CollMath::m_pi / -2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(100, 1000, 1.0f, CollMath::m_pi / -2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	// アルファ値の初期化
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
