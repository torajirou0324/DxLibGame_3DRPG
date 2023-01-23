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
	: m_arrowPosX(0)
	, m_arrowPosY(0)
	, m_arrowMoveNum(0)
	, m_intervalNum(0)
	//, m_randomNumber(0)
	//, m_EncountInterval(0)
	, m_textFlag(false)
	, m_commandIndex(0)
	, m_waitTimer(0)
{
	m_battleState = Start;

	m_blackWindow = LoadGraph("data/comand/BlackWindow.png");
	m_commandWindow[0] = LoadGraph("data/comand/commandWindow2.png");
	m_commandWindow[1] = LoadGraph("data/comand/commandWindow3.png");
	m_statusWindow = LoadGraph("data/comand/StatusWindow2.png");
	m_arrowHandle[0] = LoadGraph("data/comand/arrow3.png");
	m_arrowHandle[1] = LoadGraph("data/comand/arrow2.png");

	for (int i = 0; i < 4; i++)
	{
		m_colorFlag.push_back(true);
	}

	m_commandName.push_back("にげる");
	m_commandName.push_back("たたかう");
	m_commandName.push_back("");
	m_commandName.push_back("");

	m_pEnemy = new Enemy;
	m_pEnemy->Init("センターパート君", 30);
	m_enemyHPMAX = m_pEnemy->GetAllStatus().HP;
	m_battleState = Start;
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	delete m_pEnemy;
	m_commandName.clear();
	m_colorFlag.clear();
	DeleteGraph(m_blackWindow);
	DeleteGraph(m_statusWindow);
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(m_arrowHandle[i]);
	}

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
			//m_EncountInterval++;
		}

		if (m_pEnemy != nullptr)
		{
			delete m_pEnemy;
			m_pEnemy = nullptr;
		}

		Player::Update();
	}

	m_intervalNum++;
	if (m_intervalNum > 7)
	{
		m_intervalNum = 0;
		m_arrowMoveNum++;
		if (m_arrowMoveNum > 20)
		{
			m_arrowMoveNum = 0;
		}
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
	//printfDx("%d\n", m_randomNumber);
	//printfDx("%d\n", m_EncountInterval);
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
		m_waitTimer++;
		m_textFlag = true;
		m_arrowPosX = 1460;
		m_arrowPosY = 950;
		if (Input::IsPress(ENTER))
		{
			m_textFlag = false;
			m_battleState = Command;
			m_waitTimer = 0;
		}
		break;
	case PlayScene::Command:
		m_arrowPosX = 1370;
		CommandEvent();
		break;
	case PlayScene::Comparison:
		break;
	case PlayScene::AttackProcess:
		m_arrowPosX = 1460;
		m_arrowPosY = 950;
	{
		m_textFlag = true;
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
			m_battleState = Continue;
		}
		else
		{
			Player::SetAllStatus(resultPlayerStatus);
		}

		m_pEnemy->SetAllStatus(resultEnemyStatus);
		Player::SetAnimType(Idle);
	}
		break;
	case PlayScene::Victory:
		m_textFlag = true;
		m_arrowPosX = 1460;
		m_arrowPosY = 950;
		break;
	case PlayScene::Defeat:
		m_textFlag = true;
		m_arrowPosX = 1460;
		m_arrowPosY = 950;
		break;
	case PlayScene::Continue:
		m_battleState = Command;
		break;
	default:
		break;
	}

}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの描画処理.
//-----------------------------------------------------------------------------
void PlayScene::BattleEventDraw()
{
	auto white = GetColor(255, 255, 255);	// 白
	auto black = GetColor(0, 0, 0);			// 黒

	// プレイヤーのステータス表示用の黒枠
	{
		SetFontSize(30);
		DrawGraph(0, 750, m_statusWindow, TRUE);
		auto& playerStatus = Player::GetAllStatus();
		float berdif = static_cast<float>(playerStatus.HP) / Player::GetHPMAX();
		auto ber = 350 * berdif;
		DrawFormatString(50, 786, GetColor(255, 255, 255), "Lv.%d　　　キツキ　イチカ", playerStatus.LV);
		DrawBox(50, 870, 50 + ber, 910, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 870, 402, 910, GetColor(255, 255, 255), FALSE);
		DrawFormatString(280, 875, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, Player::GetHPMAX());
		berdif = static_cast<float>(playerStatus.EXP) / Player::GetEXPMAX();
		ber = 350 * berdif;
		DrawBox(50, 920, 50 + ber, 960, GetColor(0, 255, 255), TRUE);
		DrawBox(50, 920, 400, 960, GetColor(255, 255, 255), FALSE);
		DrawFormatString(280, 925, GetColor(255, 255, 255), "%d/%d", playerStatus.EXP, Player::GetEXPMAX());
	}


	// エネミーのステータス表示用の黒枠
	{
		DrawGraph(1400, 0, m_statusWindow, TRUE);
		auto& enemyStatus = m_pEnemy->GetAllStatus();
		float HPberdif = static_cast<float>(enemyStatus.HP) / m_enemyHPMAX;
		auto HPber = 350 * HPberdif;

		DrawFormatString(1450, 36, GetColor(255, 255, 255), "Lv.%d　　%s", enemyStatus.LV,m_pEnemy->GetName().c_str());
		DrawBox(1450, 140, 1450 + HPber, 180, GetColor(0, 255, 0), TRUE);
		DrawBox(1450, 140, 1800, 180, GetColor(255, 255, 255), FALSE);
		DrawFormatString(1680, 140, GetColor(255, 255, 255), "%d/%d", enemyStatus.HP, m_enemyHPMAX);
		SetFontSize(60);
	}

	if (m_textFlag)
	{
		DrawGraph(600, 750, m_blackWindow, TRUE);					// 吹き出しウィンドウの表示
		DrawGraph(m_arrowPosX, m_arrowPosY + m_arrowMoveNum, m_arrowHandle[m_textFlag], TRUE);	// 矢印の表示
	}
	else
	{
		for (int i = 0; i < m_commandName.size(); i++)
		{
			if (i > 1 && m_commandIndex < 2)
			{
				break;
			}
			DrawGraph(1400, 960 - 85 * i, m_commandWindow[m_colorFlag[i]], TRUE);
			DrawFormatString(1480, 970 - 85 * i, white, m_commandName[i].c_str());
		}

		DrawGraph(m_arrowPosX + m_arrowMoveNum, m_arrowPosY, m_arrowHandle[m_textFlag], TRUE);	// 矢印の表示
	}

	switch (m_battleState)
	{
	case PlayScene::Start:
	{
		SetFontSize(30);
		DrawFormatString(650, 800, white, "%sが現れた。", m_pEnemy->GetName().c_str());
		if (m_waitTimer < 60)
		{
			int gaussianScreen = MakeScreen(1920, 1080);
			GetDrawScreenGraph(0, 0, 1920, 1080, gaussianScreen);
			GraphFilter(gaussianScreen, DX_GRAPH_FILTER_GAUSS, 16, 1400);
			DrawGraph(0, 0, gaussianScreen, TRUE);
		}
	}
		break;
	case PlayScene::Command:
		break;
	case PlayScene::Comparison:
		break;
	case PlayScene::AttackProcess:
		DrawFormatString(1000, 800, GetColor(255, 255, 255), "エネミーへ%dのこうげき", Player::GetAllStatus().ATK);
		break;
	case PlayScene::Victory:
		DrawFormatString(1000, 800, GetColor(255, 255, 255), "エネミーをたおした");
		break;
	case PlayScene::Defeat:
		break;
	case PlayScene::Continue:
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの描画処理.
//-----------------------------------------------------------------------------
void PlayScene::CommandEvent()
{
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
		m_battleState = AttackProcess;
	}

	// もどる・こうげき・もちもの・へんかわざの選択処理
	if (m_commandIndex > 1 && m_commandIndex < 6)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// 下方向ボタンを押した処理

		if (m_commandIndex < 2) { m_commandIndex = 2; }
		if (m_commandIndex > 5) { m_commandIndex = 5; }

		// →の座標移動処理
		if (m_commandIndex == 2) { m_arrowPosY = 930; }
		if (m_commandIndex == 3) { m_arrowPosY = 800; }
		if (m_commandIndex == 4) { m_arrowPosY = 930; }
		if (m_commandIndex == 5) { m_arrowPosY = 800; }

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

		if (m_commandIndex == 0) { m_arrowPosY = 940; }
		if (m_commandIndex == 1) { m_arrowPosY = 1020; }

		if (Input::IsPress(ENTER) && m_commandIndex == 0) { m_commandIndex = 2; }				// たたかうコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 1) { Player::SetBattleFlag(false); }		// にげるコマンドを選択
	}

	// 敵を倒したリザルト処理
	if (m_commandIndex == 15)
	{
		//m_EncountInterval++;
		//if (m_EncountInterval == 1)
		//{
		//	auto& playerStatus = Player::GetAllStatus();
		//	auto enemyEXP = m_pEnemy->GetAllStatus().EXP;
		//	Status resultPlayerStatus = playerStatus;
		//	resultPlayerStatus.EXP = resultPlayerStatus.EXP + enemyEXP;
		//	Player::SetAllStatus(resultPlayerStatus);
		//}
		//if (m_EncountInterval > 120)
		//{
		//	Player::SetBattleFlag(false);
		//	m_commandIndex = 0;
		//	m_EncountInterval = 0;
		//}
	}
}
