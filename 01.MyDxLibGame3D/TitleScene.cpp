//-----------------------------------------------------------------------------
// @brief  タイトルシーンクラス.
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include <DxLib.h>
#include "Field.h"
#include "Input.h"
#include "AssetManager.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
TitleScene::TitleScene()
	: m_intervalNum(0)
	, m_addNum(0)
{
	
	m_TitleHandle = AssetManager::UseImage(AssetManager::Title);
	m_arrowBesideHandle = AssetManager::UseImage(AssetManager::RightArrow);
	m_arrowVerticalHandle = AssetManager::UseImage(AssetManager::DownArrow);
	m_arrowPosX = 500;
	m_arrowPosY = 640;
	m_playFlag = true;
	m_nameSettingFlag = false;
	m_BlackWindow = AssetManager::UseImage(AssetManager::BlackWindow);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
TitleScene::~TitleScene()
{
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_SCENE TitleScene::Update()
{
	SetCameraPositionAndTarget_UpVecY(VGet(5.0f, 30.0f,10.0f), VGet(5.0f, 32.0f,0.0f));

	if (Input::IsPress(LEFT))
	{
		m_arrowPosX = 150;
		m_playFlag = false;
	}
	if (Input::IsPress(RIGHT))
	{
		m_arrowPosX = 500;
		m_playFlag = true;
	}

	if (m_nameSettingFlag)
	{
		if (Input::IsPress(ENTER))
		{
			//Player::SetBattleFlag(false);
			return TAG_SCENE::TAG_PLAY;
		}
	}

	if (m_playFlag && Input::IsPress(ENTER))
	{
		m_nameSettingFlag = true;
		m_arrowPosX = 980;
		m_arrowPosY = 920;
		SetFontSize(35);
	}

	if (!m_playFlag && Input::IsPress(ENTER))
	{
		return TAG_SCENE::TAG_ESCAPE;
	}

	m_intervalNum++;
	if (m_intervalNum > 7)
	{
		m_intervalNum = 0;
		m_addNum++;
		if (m_addNum > 20)
		{
			m_addNum = 0;
		}
	}

	return TAG_SCENE::TAG_NONE;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void TitleScene::Draw()
{
	//printfDx("TitleScene\n");
	Field::DrawCall();
	DrawGraph(100, 420, m_TitleHandle, TRUE);
	if (!m_nameSettingFlag)
	{
		DrawFormatString(250, 630, GetColor(255, 255, 255), "おわる");
		DrawFormatString(600, 630, GetColor(255, 255, 255), "はじめる");

		DrawGraph(m_arrowPosX + m_addNum, m_arrowPosY, m_arrowBesideHandle, TRUE);
	}
	else
	{
		DrawExtendGraph(100, 700, 1060, 1000, m_BlackWindow, TRUE);
		//DrawGraph(100, 700, m_BlackWindow, TRUE);
		DrawFormatString(150, 760, GetColor(255, 255, 255), "あんたの名前は ”キツキ イチカ ”らしい\nこんな場所に迷い込んじまってさ　どうせなら\nたくさんモンスターを倒しレベルをあげて\nあのへやにいるやつをたおしてくれよ");
		DrawGraph(m_arrowPosX, m_arrowPosY + m_addNum, m_arrowVerticalHandle, TRUE);
	}
}
