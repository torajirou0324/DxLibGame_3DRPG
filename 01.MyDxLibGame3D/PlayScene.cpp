//-----------------------------------------------------------------------------
// @brief  プレイシーンクラス.
//-----------------------------------------------------------------------------
#include "PlayScene.h"
#include <DxLib.h>
#include "Deamon.h"
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
	, m_enemyLevelMax(2)
	, m_textFlag(false)
	, m_battleFlag(false)
	, m_enemyDeadFlag(false)
	, m_commandIndex(0)
	, m_waitTimer(0)
{
	m_normalState = Round1;
	m_battleState = Start;

	m_blackWindow = AssetManager::UseImage(AssetManager::BlackWindow);
	m_commandWindow[0] = AssetManager::UseImage(AssetManager::CommandWindowWhite);
	m_commandWindow[1] = AssetManager::UseImage(AssetManager::CommandWindowBlack);
	m_statusWindow = AssetManager::UseImage(AssetManager::StatusWindow);
	m_arrowHandle[0] = AssetManager::UseImage(AssetManager::RightArrow);
	m_arrowHandle[1] = AssetManager::UseImage(AssetManager::DownArrow);

	for (int i = 0; i < 4; i++)
	{
		m_colorFlag.push_back(true);
	}

	m_commandName.push_back("にげる");
	m_commandName.push_back("たたかう");
	m_commandName.push_back("");
	m_commandName.push_back("");
	
	m_battleState = Start;

	m_pCharacterAttackNow = nullptr;
	m_pPlayer = new Player;
	m_pPlayer->Init();
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	m_commandName.clear();
	m_colorFlag.clear();
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		delete m_pEnemyArray[i];
		m_pEnemyArray[i] = nullptr;
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
		if (Input::IsPress(ENTER))
		{
			return TAG_SCENE::TAG_END;
		}
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

	if (m_battleFlag)
	{
		BattleEventDraw();
	}
	else
	{
	}
}

void PlayScene::NormalEvent()
{
	// 敵の要素を削除
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		delete m_pEnemyArray[i];
		m_pEnemyArray[i] = nullptr;
	}
	m_pEnemyArray.clear();
	m_battleState = Start;

	// 敵を生成
	switch (m_normalState)
	{
	case PlayScene::Round1:
		for (int i = 0; i < m_normalState + 1; i++)
		{
			int level = GetRand(m_enemyLevelMax) + 1;
			auto obj = new Deamon;
			obj->Init("デーモン", level);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
		break;
	case PlayScene::Round2:
		for (int i = 0; i < m_normalState + 1; i++)
		{
			int level = GetRand(m_enemyLevelMax) + 1;
			auto obj = new Deamon;
			obj->Init("デーモン", level);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
		break;
	case PlayScene::Round3:
		for (int i = 0; i < m_normalState + 1; i++)
		{
			int level = GetRand(m_enemyLevelMax) + 1;
			auto obj = new Deamon;
			obj->Init("デーモン", level);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
		break;
	case PlayScene::Boss:
	{
		auto obj = new Deamon;
		obj->Init("デーモン", 15);
		obj->SetAttackObjectAddress(m_pPlayer);
		m_pEnemyArray.push_back(obj);
	}
		break;
	default:
		break;
	}

	m_battleFlag = true;
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの処理.
//-----------------------------------------------------------------------------
void PlayScene::BattleEvent()
{
	switch (m_battleState)
	{
	case PlayScene::Start:			// 戦闘開始処理
		m_waitTimer++;
		m_textFlag = true;
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		if (Input::IsPress(ENTER))
		{
			m_battleState = Command;
			m_waitTimer = 0;
			m_commandIndex = 0;
			m_pCharacter.push_back(m_pPlayer);
			for (int i = 0; i < m_pEnemyArray.size(); i++)
			{
				m_pCharacter.push_back(m_pEnemyArray[i]);
			}
		}
		break;
	case PlayScene::Command:		// コマンド選択処理
		m_arrowPosX = 1370;
		m_textFlag = false;
		if (m_pPlayer->GetDeathFlag())
		{
			m_battleState = Defeat;
		}
		CommandEvent();
		break;
	case PlayScene::Comparison:		// 素早さ比較処理
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		m_textFlag = true;

		for (int i = 0; i < m_pCharacter.size(); i++)
		{
			for (int j = 0; j < m_pCharacter.size(); j++)
			{
				if (i == j)
				{

				}
				else
				{
					if (m_pCharacter[i]->GetAllStatus().AGL > m_pCharacter[j]->GetAllStatus().AGL)
					{
						if (i < j)
						{

						}
						else
						{
							auto tmp = m_pCharacter[i];
							m_pCharacter[i] = m_pCharacter[j];
							m_pCharacter[j] = tmp;
						}
					}
				}
			}
		}

		m_battleState = MoveMent;
		break;
	case PlayScene::MoveMent:

		m_enemyDeadFlag = false;
		for (int i = 0; i < m_pCharacter.size(); i++)
		{
			if (!m_pCharacter[i]->GetActionFlag() && !m_pCharacter[i]->GetDeathFlag())	// 行動済みかどうか判定
			{
				m_pCharacter[i]->Attack();
				m_pCharacter[i]->Action();			// 攻撃したことを知らせる
				m_pCharacterAttackNow = m_pCharacter[i];
				break;
			}
			else
			{
				m_pCharacter[i]->Action();
			}
		}

		for (int i = 0; i < m_pCharacter.size(); i++)
		{
			if (!m_pCharacter[i]->GetDeathFlag())				// 死んでいるかどうか
			{
				if (m_pCharacter[i]->GetAllStatus().HP <= 0)
				{
					m_pCharacter[i]->Dead();
					if (m_pCharacter[i]->GetCharaName() == UnHuman)
					{
						int EXP = m_pCharacter[i]->GetAllStatus().EXP;
						m_pPlayer->EXPAdd(EXP);
					}
				}
				if (m_pCharacter[i]->GetCharaName() == UnHuman)
				{
					m_enemyDeadFlag = true;
				}
			}
			else
			{
				if (m_pCharacter[i]->GetCharaName() == Human)
				{
					m_battleState = Defeat;
					break;
				}
			}
		}

		if (m_battleState != Defeat)
		{
			if (m_enemyDeadFlag)
			{
				m_battleState = AttackProcess;
			}
			else
			{
				m_battleState = Victory;
			}
		}

		break;
	case PlayScene::AttackProcess:
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		m_textFlag = true;
		m_waitTimer++;

		if (m_waitTimer > 120)
		{
			m_battleState = Continue;
			m_waitTimer = 0;
		}

		break;
	case PlayScene::Victory:		// 勝利処理
		m_textFlag = true;
		m_arrowPosX = 1240;
		m_arrowPosY = 950;

		if (Input::IsPress(ENTER))
		{
			m_battleFlag = false;
			for (int i = 0; i < m_pCharacter.size(); i++)
			{
				m_pCharacter[i]->ActionInit();
			}
			m_pCharacter.clear();
			int EventNum = m_normalState;
			EventNum++;
			if (EventNum > Boss)
			{
				EventNum = Boss;
			}
			m_normalState = static_cast<NormalState>(EventNum);
		}
		break;
	case PlayScene::Defeat:			// 敗北処理
		m_textFlag = true;
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		if (Input::IsPress(ENTER))
		{
			m_battleFlag = false;
			for (int i = 0; i < m_pCharacter.size(); i++)
			{
				m_pCharacter[i]->ActionInit();
			}
			m_pCharacter.clear();
		}
		break;
	case PlayScene::Escape:			// 逃げる処理
		m_textFlag = true;
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		if (Input::IsPress(ENTER))
		{
			m_battleFlag = false;
			for (int i = 0; i < m_pCharacter.size(); i++)
			{
				m_pCharacter[i]->ActionInit();
			}
			m_pCharacter.clear();
			if (m_normalState == Boss)
			{
				m_enemyLevelMax++;
			}
			m_normalState = Round1;
		}
		break;
	case PlayScene::Continue:		// ターン継続処理
		m_battleState = Command;
		m_commandIndex = 0;

		for (int i = 0; i < m_pCharacter.size(); i++)
		{
			if (!m_pCharacter[i]->GetActionFlag())
			{
				m_battleState = MoveMent;
				break;
			}
		}

		if (m_battleState == Command)
		{
			for (int i = 0; i < m_pCharacter.size(); i++)
			{
				m_pCharacter[i]->ActionInit();
			}
		}
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

	DrawGraph(600, 750, m_blackWindow, TRUE);					// 吹き出しウィンドウの表示

	if (m_textFlag)
	{
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
			if (m_colorFlag[i])
			{
				DrawFormatString(1480, 970 - 85 * i, white, m_commandName[i].c_str());
			}
			else
			{
				DrawFormatString(1480, 970 - 85 * i, black, m_commandName[i].c_str());
			}

		}
		DrawGraph(m_arrowPosX + m_arrowMoveNum, m_arrowPosY, m_arrowHandle[m_textFlag], TRUE);	// 矢印の表示
	}

	SetFontSize(30);
	// プレイヤーのステータス表示用の黒枠
	{
		DrawGraph(0, 750, m_statusWindow, TRUE);
		auto& playerStatus = m_pPlayer->GetAllStatus();
		float berdif = static_cast<float>(playerStatus.HP) / m_pPlayer->GetHPMAX();
		auto ber = 350 * berdif;
		DrawFormatString(50, 786, GetColor(255, 255, 255), "Lv.%d　　　キツキ　イチカ", playerStatus.LV);
		DrawBox(50, 870, 50 + ber, 910, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 868, 402, 912, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 883, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, m_pPlayer->GetHPMAX());
		berdif = static_cast<float>(playerStatus.EXP) / m_pPlayer->GetEXPMAX();
		ber = 350 * berdif;
		DrawBox(50, 920, 50 + ber, 960, GetColor(0, 255, 255), TRUE);
		DrawBox(48, 918, 402, 962, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 927, GetColor(255, 255, 255), "%d/%d", playerStatus.EXP, m_pPlayer->GetEXPMAX());
	}

	// エネミーのステータス表示用の黒枠
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

	switch (m_battleState)
	{
	case PlayScene::Start:
	{
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			DrawFormatString(650, 800 + 60 * i, white, "%sが現れた。", m_pEnemyArray[i]->GetName().c_str());
		}
		
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
		DrawFormatString(650, 800, white, "コマンド選択中...");
		break;
	case PlayScene::Comparison:
		break;
	case PlayScene::AttackProcess:
		DrawLine(1100, 0, 1500, 1080, 10 * (120 - m_waitTimer));
		DrawFormatString(650, 800, white, "Lv%d:%sがこうげき",m_pCharacterAttackNow->GetAllStatus().LV, m_pCharacterAttackNow->GetName().c_str());
		break;
	case PlayScene::Victory:
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			DrawFormatString(650, 800 + 60 * i, white, "%sをたおした", m_pEnemyArray[i]->GetName().c_str());
		}
		break;
	case PlayScene::Defeat:
		DrawFormatString(650, 800, white, "キツキ　イチカは倒れた");
		break;
	case PlayScene::Continue:
		break;
	default:
		break;
	}
	SetFontSize(60);
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントの描画処理.
//-----------------------------------------------------------------------------
void PlayScene::CommandEvent()
{
	for (int i = 0; i < 4; i++)
	{
		m_colorFlag[i] = true;
		m_commandName[i] = "";
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
	if (m_commandIndex > 5 && m_commandIndex < 10)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// 下方向ボタンを押した処理

		if (m_commandIndex < 6) { m_commandIndex = 6; }
		if (m_commandIndex > 6 + m_pEnemyArray.size()) { m_commandIndex = 6 + m_pEnemyArray.size(); }

		// →の座標移動処理
		if (m_commandIndex == 6) { m_arrowPosY = 975; m_colorFlag[0] = false; }
		if (m_commandIndex == 7) { m_arrowPosY = 890; m_colorFlag[1] = false; }
		if (m_commandIndex == 8) { m_arrowPosY = 805; m_colorFlag[2] = false; }
		if (m_commandIndex == 9) { m_arrowPosY = 720; m_colorFlag[3] = false; }

		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			if (m_commandIndex == 6 + i)
			{
				if (Input::IsPress(ENTER) && !m_pEnemyArray[i]->GetDeathFlag())
				{
					m_pPlayer->SetAttackObjectAddress(m_pEnemyArray[i]);
					m_battleState = Comparison;
				}
			}

			m_commandName[i] = m_pEnemyArray[i]->GetName();
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
		if (m_commandIndex == 2) { m_arrowPosY = 975; m_colorFlag[0] = false; }
		if (m_commandIndex == 3) { m_arrowPosY = 890; m_colorFlag[1] = false; }
		if (m_commandIndex == 4) { m_arrowPosY = 805; m_colorFlag[2] = false; }
		if (m_commandIndex == 5) { m_arrowPosY = 720; m_colorFlag[3] = false; }

		if (Input::IsPress(ENTER) && m_commandIndex == 2) { m_commandIndex = 0; }		// もどるコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 3) { m_commandIndex = 6; }		// こうげきコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 4) { m_commandIndex = 7; }		// へんかわざを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 5) { m_commandIndex = 11; }		// もちものを選択

		m_commandName[0] = "もどる";
		m_commandName[1] = "こうげき";
		m_commandName[2] = "とくしゅ";
		m_commandName[3] = "もちもの";
	}
	// たたかう・にげるかの選択処理
	else if (m_commandIndex < 2)
	{
		if (Input::IsPress(UP)) { m_commandIndex = 1; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex = 0; }	// 下方向ボタンを押した処理

		if (m_commandIndex == 1) { m_arrowPosY = 890; m_colorFlag[1] = false; }
		if (m_commandIndex == 0) { m_arrowPosY = 975; m_colorFlag[0] = false; }

		if (Input::IsPress(ENTER) && m_commandIndex == 1) { m_commandIndex = 2; }		// たたかうコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 0) { m_battleState = Escape; }		// にげるコマンドを選択

		m_commandName[0] = "にげる";
		m_commandName[1] = "たたかう";
		m_commandName[2] = "";
		m_commandName[3] = "";
	}
}
