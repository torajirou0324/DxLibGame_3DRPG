//-----------------------------------------------------------------------------
// @brief  タイトルシーンクラス.
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Field.h"
#include "Input.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
TitleScene::TitleScene()
{
	m_TitleCommand = LoadGraph("data/Title/Title.png");
	m_arrowHandle = LoadGraph("data/comand/arrow.png");
	m_arrowPosX = 500;
	m_playFlag = true;
	Player::InitCall();
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
TitleScene::~TitleScene()
{
	DeleteGraph(m_TitleCommand);
	DeleteGraph(m_arrowHandle);
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_SCENE TitleScene::Update()
{
	Player::Update();
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

	if (m_playFlag && Input::IsPress(ENTER))
	{
		Player::SetBattleFlag(false);
		return TAG_SCENE::TAG_PLAY;
	}
	if (!m_playFlag && Input::IsPress(ENTER))
	{
		return TAG_SCENE::TAG_ESCAPE;
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
	Player::DrawCall();
	DrawGraph(100, 420, m_TitleCommand, TRUE);
	DrawFormatString(250, 630, GetColor(255, 255, 255), "おわる");
	DrawFormatString(600, 630, GetColor(255, 255, 255), "はじめる");
	DrawGraph(m_arrowPosX, 630, m_arrowHandle, TRUE);
}
