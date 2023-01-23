//-----------------------------------------------------------------------------
// @brief  �^�C�g���V�[���N���X.
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Field.h"
#include "Input.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
TitleScene::TitleScene()
	: m_intervalNum(0)
	, m_addNum(0)
{
	m_TitleHandle = LoadGraph("data/Title/Title.png");
	m_arrowBesideHandle = LoadGraph("data/comand/arrow3.png");
	m_arrowVerticalHandle = LoadGraph("data/comand/arrow2.png");
	m_arrowPosX = 500;
	m_arrowPosY = 640;
	m_playFlag = true;
	m_nameSettingFlag = false;
	m_BlackWindow = LoadGraph("data/comand/BlackWindow.png");
	Player::InitCall();
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
TitleScene::~TitleScene()
{
	DeleteGraph(m_TitleHandle);
	DeleteGraph(m_arrowBesideHandle);
	DeleteGraph(m_arrowVerticalHandle);
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
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
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void TitleScene::Draw()
{
	//printfDx("TitleScene\n");
	Field::DrawCall();
	Player::DrawCall();
	DrawGraph(100, 420, m_TitleHandle, TRUE);
	if (!m_nameSettingFlag)
	{
		DrawFormatString(250, 630, GetColor(255, 255, 255), "�����");
		DrawFormatString(600, 630, GetColor(255, 255, 255), "�͂��߂�");

		DrawGraph(m_arrowPosX + m_addNum, m_arrowPosY, m_arrowBesideHandle, TRUE);
	}
	else
	{
		DrawGraph(100, 700, m_BlackWindow, TRUE);
		DrawFormatString(150, 760, GetColor(255, 255, 255), "���񂽂̖��O�� �h�L�c�L �C�`�J �h�炵��\n����ȏꏊ�ɖ������񂶂܂��Ă��@�ǂ����Ȃ�\n�������񃂃��X�^�[��|�����x����������\n���̂ւ�ɂ������������Ă����");
		DrawGraph(m_arrowPosX, m_arrowPosY + m_addNum, m_arrowVerticalHandle, TRUE);
	}
}
