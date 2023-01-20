//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#include "PlayScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Enemy.h"
#include "Field.h"
#include "Input.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
PlayScene::PlayScene()
	: m_arrowPosX(1540)
	, m_arrowPosY(800)
	, m_randomNumber(0)
	, m_EncountInterval(0)
	, m_commandIndex(0)
	, m_waitTimer(0)
{
	m_battleState = Start;

	m_blackWindow = LoadGraph("data/comand/BlackWindow2.png");
	m_commandWindow[0] = LoadGraph("data/comand/commandWindow2.png");
	m_commandWindow[1] = LoadGraph("data/comand/commandWindow3.png");
	m_statusWindow = LoadGraph("data/comand/StatusWindow2.png");
	m_arrowHandle = LoadGraph("data/comand/arrow3.png");
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	delete m_pEnemy;

	DeleteGraph(m_blackWindow);
	DeleteGraph(m_statusWindow);
	DeleteGraph(m_arrowHandle);
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_SCENE PlayScene::Update()
{
	if (Player::GetBattleFlag())
	{
		BattleEvent();
	}
	else
	{
		if (Input::IsPress(ENTER))
		{
			return TAG_SCENE::TAG_END;
		}

		if (Player::GetAnimType() == Walk)
		{
			m_EncountInterval++;
		}

		if (m_pEnemy != nullptr)
		{
			delete m_pEnemy;
			m_pEnemy = nullptr;
		}

		if (m_EncountInterval > 180)
		{
			m_randomNumber = GetRand(2);
			if (m_randomNumber == 0)
			{
				Player::SetBattleFlag(true);
				if (m_pEnemy == nullptr)
				{
					m_pEnemy = new Enemy;
					m_enemyHPMAX = m_pEnemy->GetAllStatus().HP;
				}
			}
			m_EncountInterval = 0;
		}

		Player::Update();
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
	printfDx("%d\n", m_randomNumber);
	printfDx("%d\n", m_EncountInterval);
	Field::DrawCall();

	if (Player::GetBattleFlag())
	{
		m_pEnemy->Draw();
		BattleEventDraw();
	}
	else
	{
		Player::DrawCall();
	}
}

void PlayScene::NormalEvent()
{
	Player::Update();
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの処理.
//-----------------------------------------------------------------------------
void PlayScene::BattleEvent()
{
	switch (m_battleState)
	{
	case PlayScene::Start:
		break;
	case PlayScene::Wait:
		break;
	case PlayScene::Command:
		break;
	case PlayScene::Comparison:
		break;
	case PlayScene::AttackProcess:
		break;
	case PlayScene::Victory:
		break;
	case PlayScene::Defeat:
		break;
	case PlayScene::Continue:
		break;
	default:
		break;
	}

	// コマンド：もちものの選択後処理
	if (m_commandIndex > 10 && m_commandIndex < 15)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// 下方向ボタンを押した処理

		if (m_commandIndex < 11) { m_commandIndex = 11; }
		if (m_commandIndex > 14) { m_commandIndex = 14; }
	}

	// コマンド：へんかわざの選択後処理
	if (m_commandIndex > 6 && m_commandIndex < 11)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// 下方向ボタンを押した処理

		if (m_commandIndex < 7) { m_commandIndex = 7; }
		if (m_commandIndex > 10) { m_commandIndex = 10; }
	}

	// コマンド：こうげきの選択後処理
	if (m_commandIndex == 6)
	{
		// こうげきアニメーションが終了したか判定
		if (Player::GetAnimTime() >= Player::GetAnimTotalTime())
		{
			m_commandIndex = 0;
			// こうげきアニメーションが終了したので次の処理に移る
			auto& playerStatus = Player::GetAllStatus();
			auto& enemyStatus = m_pEnemy->GetAllStatus();
			Status resultEnemyStatus = enemyStatus;
			Status resultPlayerStatus = playerStatus;
			resultEnemyStatus.HP = enemyStatus.HP - playerStatus.ATK;
			resultPlayerStatus.HP = resultPlayerStatus.HP - enemyStatus.ATK;
			if (resultEnemyStatus.HP <= 0) 
			{ 
				resultEnemyStatus.HP = 0;
				m_commandIndex = 15;
			}
			else
			{
				Player::SetAllStatus(resultPlayerStatus);
			}

			m_pEnemy->SetAllStatus(resultEnemyStatus);
			Player::SetAnimType(Idle);
		}
	}

	// もどる・こうげき・もちもの・へんかわざの選択処理
	if (m_commandIndex > 1 && m_commandIndex < 6)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// 下方向ボタンを押した処理

		if (m_commandIndex < 2) { m_commandIndex = 2; }
		if (m_commandIndex > 5) { m_commandIndex = 5; }

		// →の座標移動処理
		if (m_commandIndex == 2) { m_arrowPosX = 900; m_arrowPosY = 930; }
		if (m_commandIndex == 3) { m_arrowPosX = 900; m_arrowPosY = 800; }
		if (m_commandIndex == 4) { m_arrowPosX = 1400; m_arrowPosY = 930; }
		if (m_commandIndex == 5) { m_arrowPosX = 1400; m_arrowPosY = 800; }

		if (Input::IsPress(ENTER) && m_commandIndex == 2) { m_commandIndex = 0; }		// もどるコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 3) { m_commandIndex = 6; Player::SetAnimType(Attack); }	// こうげきコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 4) { m_commandIndex = 7; }		// へんかわざを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 5) { m_commandIndex = 11; }		// もちものを選択
	}
	// たたかう・にげるかの選択処理
	else if (m_commandIndex < 2)
	{
		if (Input::IsPress(UP)) { m_commandIndex = 0; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex = 1; }	// 下方向ボタンを押した処理

		if(m_commandIndex == 0) { m_arrowPosY = 940; }
		if(m_commandIndex == 1) { m_arrowPosY = 1020; }

		if (Input::IsPress(ENTER) && m_commandIndex == 0) { m_commandIndex = 2; }				// たたかうコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 1) { Player::SetBattleFlag(false); }		// にげるコマンドを選択
	}

	// 敵を倒したリザルト処理
	if (m_commandIndex == 15)
	{
		m_EncountInterval++;
		if (m_EncountInterval == 1)
		{
			auto& playerStatus = Player::GetAllStatus();
			auto enemyEXP = m_pEnemy->GetAllStatus().EXP;
			Status resultPlayerStatus = playerStatus;
			resultPlayerStatus.EXP = resultPlayerStatus.EXP + enemyEXP;
			Player::SetAllStatus(resultPlayerStatus);
		}
		if (m_EncountInterval > 120)
		{
			Player::SetBattleFlag(false);
			m_commandIndex = 0;
			m_EncountInterval = 0;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの描画処理.
//-----------------------------------------------------------------------------
void PlayScene::BattleEventDraw()
{
	// プレイヤーのステータス表示用の黒枠
	{
		SetFontSize(30);
		DrawGraph(0, 834, m_statusWindow, TRUE);
		auto& playerStatus = Player::GetAllStatus();
		float berdif = static_cast<float>(playerStatus.HP) / Player::GetHPMAX();
		auto ber = 350 * berdif;
		DrawFormatString(50, 870, GetColor(255, 255, 255), "Lv.%d　　　キツキ　イチカ", playerStatus.LV);
		DrawBox(50, 940, 50 + ber, 980, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 938, 402, 982, GetColor(255, 255, 255), FALSE);
		DrawFormatString(280, 945, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, Player::GetHPMAX());
		berdif = static_cast<float>(playerStatus.EXP) / Player::GetEXPMAX();
		ber = 350 * berdif;
		DrawBox(50, 990, 50 + ber, 1030, GetColor(0, 255, 255), TRUE);
		DrawBox(50, 990, 400, 1030, GetColor(255, 255, 255), FALSE);
		DrawFormatString(280, 990, GetColor(255, 255, 255), "%d/%d", playerStatus.EXP, Player::GetEXPMAX());
	}


	// エネミーのステータス表示用の黒枠
	{
		DrawGraph(1400, 0, m_statusWindow, TRUE);
		auto& enemyStatus = m_pEnemy->GetAllStatus();
		float HPberdif = static_cast<float>(enemyStatus.HP) / m_enemyHPMAX;
		auto HPber = 350 * HPberdif;

		DrawFormatString(1450, 36, GetColor(255, 255, 255), "Lv.%d", enemyStatus.LV);
		DrawBox(1450, 140, 1450 + HPber, 180, GetColor(0, 255, 0), TRUE);
		DrawBox(1450, 140, 1800, 180, GetColor(255, 255, 255), FALSE);
		DrawFormatString(1680, 140, GetColor(255, 255, 255), "%d/%d", enemyStatus.HP, m_enemyHPMAX);
		SetFontSize(60);
	}

	auto white = GetColor(255, 255, 255);
	auto black = GetColor(0, 0, 0);
	if (m_commandIndex < 2)
	{
		DrawGraph(1520, 1000, m_commandWindow[1], TRUE);			// にげるウィンドウの表示
		DrawFormatString(1600, 1010, black, "にげる");

		DrawGraph(1520, 920, m_commandWindow[1], TRUE);				// たたかうウィンドウの表示
		DrawFormatString(1600, 930, black, "たたかう");

		DrawGraph(m_arrowPosX, m_arrowPosY, m_arrowHandle, TRUE);	// 矢印の表示
	}

	if (m_commandIndex > 1 && m_commandIndex < 6)
	{
		DrawGraph(0, 718, m_blackWindow, TRUE);					// 吹き出しウィンドウの表示
		DrawGraph(m_arrowPosX, m_arrowPosY, m_arrowHandle, TRUE);	// 矢印の表示

		DrawFormatString(1000, 800, GetColor(255, 255, 255), "こうげき");
		DrawFormatString(1500, 800, GetColor(255, 255, 255), "もちもの");
		DrawFormatString(1500, 930, GetColor(255, 255, 255), "へんかわざ");
		DrawFormatString(1000, 930, GetColor(255, 255, 255), "もどる");
	}

	if (m_commandIndex == 6)
	{
		DrawGraph(840, 718, m_blackWindow, TRUE);					// 吹き出しウィンドウの表示
		DrawFormatString(1000, 800, GetColor(255, 255, 255), "エネミーへ%dのこうげき", Player::GetAllStatus().ATK);
	}

	if (m_commandIndex == 15)
	{
		DrawGraph(840, 718, m_blackWindow, TRUE);					// 吹き出しウィンドウの表示
		DrawFormatString(1000, 800, GetColor(255, 255, 255), "エネミーをたおした");
	}
}
