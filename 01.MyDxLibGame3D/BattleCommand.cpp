//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理クラス.
//-----------------------------------------------------------------------------
#include "BattleCommand.h"
#include "Input.h"
#include "ArrowSymbol.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleCommand::BattleCommand()
	: m_arrowPosY(0)
	, m_selectFlag(false)
	, m_escapeFlag(false)
	, m_arrowMoveNum(0)		// コマンド選択矢印の微動させる用変数.
	, m_intervalNum(0)
{
	m_commandWindow[0] = AssetManager::UseImage(AssetManager::CommandWindowWhite);
	m_commandWindow[1] = AssetManager::UseImage(AssetManager::CommandWindowBlack);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleCommand::~BattleCommand()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleCommand::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
	m_pCharacter = character;
	m_pCharacterAttackNow = attackNowCharacter;
	m_pPlayScene = playScene;
	m_commandIndex = 1;
	m_enemyAllNum = m_pCharacter.size() - 1;
	for (int i = 0; i < 4; i++)
	{
		m_colorFlag[i] = true;
		m_commandName[i] = "";
	}
	m_selectFlag = false;
	m_escapeFlag = false;
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_BattleState BattleCommand::Update()
{
	CommandSelectProcess();
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
	// 逃げるコマンドが選択されたためESCAPE処理へ
	if (m_escapeFlag)
	{
		return TAG_BattleState::BattleEscapeProcess;
	}
	// 戦闘コマンドが選択されたため素早さ比較処理へ
    if (m_selectFlag)
    {
        return TAG_BattleState::Comparison;
    }

    return TAG_BattleState::None;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleCommand::Draw()
{
	DrawFormatString(650, 800, GetColor(255, 255, 255), "コマンド選択中...");

	SetFontSize(60);
	for (int i = 0; i < 4; i++)
	{
		if (i > 1 && m_commandIndex < 2)
		{
			break;
		}
		DrawGraph(1400, 960 - 85 * i, m_commandWindow[m_colorFlag[i]], TRUE);
		if (m_colorFlag[i])
		{
			DrawFormatString(1480, 970 - 85 * i, GetColor(255, 255, 255), m_commandName[i].c_str());
		}
		else
		{
			DrawFormatString(1480, 970 - 85 * i, GetColor(0, 0, 0), m_commandName[i].c_str());
		}

	}

	DrawArrowSide(1370 + m_arrowMoveNum, m_arrowPosY); // 矢印の表示
	//DrawGraph(m_arrowPosX + m_arrowMoveNum, m_arrowPosY, m_arrowHandle[m_textFlag], TRUE);
}

//-----------------------------------------------------------------------------
// @brief  バトルイベントのコマンド選択処理.
//-----------------------------------------------------------------------------
void BattleCommand::CommandSelectProcess()
{
	for (int i = 0; i < 4; i++)
	{
		m_colorFlag[i] = true;
		m_commandName[i] = "";
	}

	// コマンド：こうげきのこうげき目標選択処理
	if (m_commandIndex > 5 && m_commandIndex < 10)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// 下方向ボタンを押した処理

		if (m_commandIndex < 6) { m_commandIndex = 6; }
		if (m_commandIndex > 6 + m_enemyAllNum) { m_commandIndex = 6 + m_enemyAllNum; }

		for (int i = 0; i < 4; i++)
		{
			if (m_commandIndex == 6 + i)
			{
				// →の座標移動処理
				m_arrowPosY = 975 - (85 * i); m_colorFlag[i] = false;

				if (i < 1)
				{
					if (Input::IsPress(ENTER) && m_commandIndex == 6) { m_commandIndex = 5;  return; }		// もどるコマンドを選択
				}
				else if (Input::IsPress(ENTER) && !m_pCharacter[i]->GetDeathFlag())
				{
					// プレイヤーの攻撃目標に敵を代入
					m_pCharacter[0]->SetAttackObjectAddress(m_pCharacter[i]);
					m_selectFlag = true;
				}
			}

			if (i > 0 && i <= m_enemyAllNum)
			{
				m_commandName[i] = m_pCharacter[i]->GetName();
			}
		}
		m_commandName[0] = "もどる";
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

		if (Input::IsPress(ENTER) && m_commandIndex == 5) { m_commandIndex = 9; }				// こうげきコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 4) { m_commandIndex = 9; }				// とくしゅを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 3 /*&& m_healFlag*/)	// かいふくを選択
		{
			//m_pPlayer->HPHeal();
			//m_healFlag = false;
			m_selectFlag = true;
		}
		if (Input::IsPress(ENTER) && m_commandIndex == 2) { m_commandIndex = 1; return; }		// もどるコマンドを選択

		m_commandName[0] = "もどる";
		m_commandName[2] = "とくしゅ";
		m_commandName[3] = "こうげき";
		//if (m_healFlag)
		//{
		//	m_commandName[1] = "かいふく○";
		//}
		//else
		//{
			m_commandName[1] = "かいふく";
		//}
	}
	// たたかう・にげるかの選択処理
	if (m_commandIndex < 2)
	{
		if (Input::IsPress(UP)) { m_commandIndex = 1; }		// 上方向ボタンを押した処理
		if (Input::IsPress(DOWN)) { m_commandIndex = 0; }	// 下方向ボタンを押した処理

		if (m_commandIndex == 1) { m_arrowPosY = 890; m_colorFlag[1] = false; }
		if (m_commandIndex == 0) { m_arrowPosY = 975; m_colorFlag[0] = false; }

		if (Input::IsPress(ENTER) && m_commandIndex == 1) { m_commandIndex = 5; }		// たたかうコマンドを選択
		if (Input::IsPress(ENTER) && m_commandIndex == 0) { m_escapeFlag = true; }	// にげるコマンドを選択

		m_commandName[0] = "にげる";
		m_commandName[1] = "たたかう";
		m_commandName[2] = "ステータス";
	}
}
