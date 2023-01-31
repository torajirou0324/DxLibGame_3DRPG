//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#include "PlayScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Deamon.h"
#include "Field.h"
#include "Input.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
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

	m_commandName.push_back("�ɂ���");
	m_commandName.push_back("��������");
	m_commandName.push_back("");
	m_commandName.push_back("");
	auto player = Player::GetAddress();
	m_pCharacter.push_back(player);
	for (int i = 1; i < 4; i++)
	{
		auto obj = new Deamon;
		obj->Init("�Z���^�[�p�[�g", i);
		m_pCharacter.push_back(obj);
	}
	
	m_battleState = Start;
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	m_commandName.clear();
	m_colorFlag.clear();
	for (int i = 0; i < m_pCharacter.size(); i++)
	{
		delete m_pCharacter[i];
		m_pCharacter[i] = nullptr;
	}
	m_pCharacter.clear();
	DeleteGraph(m_blackWindow);
	DeleteGraph(m_statusWindow);
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(m_arrowHandle[i]);
	}

}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
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
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::Draw()
{
	// �f�o�b�O�p������{�ϐ��l�`��
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
// @brief  �o�g���C�x���g�̏���.
//-----------------------------------------------------------------------------
void PlayScene::BattleEvent()
{
	switch (m_battleState)
	{
	case PlayScene::Start:			// �퓬�J�n����
		m_waitTimer++;
		m_textFlag = true;
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		if (Input::IsPress(ENTER))
		{
			m_battleState = Command;
			m_waitTimer = 0;
		}
		break;
	case PlayScene::Command:		// �R�}���h�I������
		m_arrowPosX = 1370;
		m_textFlag = false;
		CommandEvent();
		break;
	case PlayScene::Comparison:		// �f������r����

		break;
	case PlayScene::AttackProcess:	// �v���C���[�̍U������
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		m_textFlag = true;
	{
		m_commandIndex = 0;
		// ���������A�j���[�V�������I�������̂Ŏ��̏����Ɉڂ�
		auto& playerStatus = Player::GetAllStatus();
		auto& enemyStatus = m_pEnemy->GetAllStatus();
		Status resultEnemyStatus = enemyStatus;
		Status resultPlayerStatus = playerStatus;
		resultEnemyStatus.HP = enemyStatus.HP - playerStatus.ATK;

		if (resultEnemyStatus.HP <= 0)
		{
			resultEnemyStatus.HP = 0;
			resultPlayerStatus.EXP = playerStatus.EXP + enemyStatus.EXP;
			Player::SetAllStatus(resultPlayerStatus);
			m_battleState = Victory;
		}
		else
		{
			m_pEnemy->SetAllStatus(resultEnemyStatus);
			m_battleState = Comparison;
		}
	}
		break;
	case PlayScene::DamageProcess:	// �v���C���[�̔�_������
	{
		m_arrowPosX = 1240;
		m_arrowPosY = 950;

		auto& playerStatus = Player::GetAllStatus();
		auto& enemyStatus = m_pEnemy->GetAllStatus();
		Status resultEnemyStatus = enemyStatus;
		Status resultPlayerStatus = playerStatus;
		resultPlayerStatus.HP = resultPlayerStatus.HP - enemyStatus.ATK;

		Player::SetAllStatus(resultPlayerStatus);
	}
		break;
	case PlayScene::Victory:		// ��������
		m_textFlag = true;
		m_arrowPosX = 1240;
		m_arrowPosY = 950;

		Player::LevelManager();
		if (Input::IsPress(ENTER))
		{
			Player::SetBattleFlag(false);
		}
		break;
	case PlayScene::Defeat:			// �s�k����
		m_textFlag = true;
		m_arrowPosX = 1240;
		m_arrowPosY = 950;
		if (Input::IsPress(ENTER))
		{
			Player::SetBattleFlag(false);
		}
		break;
	case PlayScene::Continue:		// �^�[���p������
		m_battleState = Command;
		break;
	default:
		break;
	}

}

//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̕`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::BattleEventDraw()
{
	auto white = GetColor(255, 255, 255);	// ��
	auto black = GetColor(0, 0, 0);			// ��

	DrawGraph(600, 750, m_blackWindow, TRUE);					// �����o���E�B���h�E�̕\��

	if (m_textFlag)
	{
		DrawGraph(m_arrowPosX, m_arrowPosY + m_arrowMoveNum, m_arrowHandle[m_textFlag], TRUE);	// ���̕\��
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
		DrawGraph(m_arrowPosX + m_arrowMoveNum, m_arrowPosY, m_arrowHandle[m_textFlag], TRUE);	// ���̕\��
	}

	SetFontSize(30);
	// �v���C���[�̃X�e�[�^�X�\���p�̍��g
	{
		DrawGraph(0, 750, m_statusWindow, TRUE);
		auto& playerStatus = Player::GetAllStatus();
		float berdif = static_cast<float>(playerStatus.HP) / Player::GetHPMAX();
		auto ber = 350 * berdif;
		DrawFormatString(50, 786, GetColor(255, 255, 255), "Lv.%d�@�@�@�L�c�L�@�C�`�J", playerStatus.LV);
		DrawBox(50, 870, 50 + ber, 910, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 870, 402, 910, GetColor(255, 255, 255), FALSE);
		DrawFormatString(280, 875, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, Player::GetHPMAX());
		berdif = static_cast<float>(playerStatus.EXP) / Player::GetEXPMAX();
		ber = 350 * berdif;
		DrawBox(50, 920, 50 + ber, 960, GetColor(0, 255, 255), TRUE);
		DrawBox(50, 920, 400, 960, GetColor(255, 255, 255), FALSE);
		DrawFormatString(280, 925, GetColor(255, 255, 255), "%d/%d", playerStatus.EXP, Player::GetEXPMAX());
	}

	// �G�l�~�[�̃X�e�[�^�X�\���p�̍��g
	{
		DrawGraph(1400, 0, m_statusWindow, TRUE);
		auto& enemyStatus = m_pEnemy->GetAllStatus();
		float HPberdif = static_cast<float>(enemyStatus.HP) / m_enemyHPMAX;
		auto HPber = 350 * HPberdif;

		DrawFormatString(1450, 36, GetColor(255, 255, 255), "Lv.%d�@�@%s", enemyStatus.LV,m_pEnemy->GetName().c_str());
		DrawBox(1450, 140, 1450 + HPber, 180, GetColor(0, 255, 0), TRUE);
		DrawBox(1450, 140, 1800, 180, GetColor(255, 255, 255), FALSE);
		DrawFormatString(1680, 140, GetColor(255, 255, 255), "%d/%d", enemyStatus.HP, m_enemyHPMAX);
	}

	switch (m_battleState)
	{
	case PlayScene::Start:
	{
		DrawFormatString(650, 800, white, "%s�����ꂽ�B", m_pEnemy->GetName().c_str());
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
		DrawFormatString(650, 800, white, "�R�}���h�I��...");
		break;
	case PlayScene::Comparison:
		break;
	case PlayScene::AttackProcess:
		DrawFormatString(650, 800, white, "�G�l�~�[��%d�̂�������", Player::GetAllStatus().ATK);
		break;
	case PlayScene::DamageProcess:
		break;
	case PlayScene::Victory:
		DrawFormatString(650, 800, white, "%s����������", m_pEnemy->GetName().c_str());
		break;
	case PlayScene::Defeat:
		break;
	case PlayScene::Continue:
		break;
	default:
		break;
	}
	SetFontSize(60);
}

//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̕`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::CommandEvent()
{
	for (int i = 0; i < 4; i++)
	{
		m_colorFlag[i] = true;
	}

	// �R�}���h�F�������̂̑I���㏈��
	if (m_commandIndex > 10 && m_commandIndex < 15)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// �������{�^��������������

		if (m_commandIndex < 11) { m_commandIndex = 11; }
		if (m_commandIndex > 14) { m_commandIndex = 14; }
	}

	// �R�}���h�F�ւ񂩂킴�̑I���㏈��
	if (m_commandIndex > 6 && m_commandIndex < 11)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// �������{�^��������������

		if (m_commandIndex < 7) { m_commandIndex = 7; }
		if (m_commandIndex > 10) { m_commandIndex = 10; }
	}

	// �R�}���h�F���������̑I���㏈��
	if (m_commandIndex == 6)
	{
		m_battleState = Comparison;
	}

	// ���ǂ�E���������E�������́E�ւ񂩂킴�̑I������
	if (m_commandIndex > 1 && m_commandIndex < 6)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// �������{�^��������������

		if (m_commandIndex < 2) { m_commandIndex = 2; }
		if (m_commandIndex > 5) { m_commandIndex = 5; }

		// ���̍��W�ړ�����
		if (m_commandIndex == 2) { m_arrowPosY = 975; m_colorFlag[0] = false; }
		if (m_commandIndex == 3) { m_arrowPosY = 890; m_colorFlag[1] = false; }
		if (m_commandIndex == 4) { m_arrowPosY = 805; m_colorFlag[2] = false; }
		if (m_commandIndex == 5) { m_arrowPosY = 720; m_colorFlag[3] = false; }

		if (Input::IsPress(ENTER) && m_commandIndex == 2) { m_commandIndex = 0; }		// ���ǂ�R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 3) { m_commandIndex = 6; }		// ���������R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 4) { m_commandIndex = 7; }		// �ւ񂩂킴��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 5) { m_commandIndex = 11; }		// �������̂�I��

		m_commandName[0] = "���ǂ�";
		m_commandName[1] = "��������";
		m_commandName[2] = "�Ƃ�����";
		m_commandName[3] = "��������";
	}
	// ���������E�ɂ��邩�̑I������
	else if (m_commandIndex < 2)
	{
		if (Input::IsPress(UP)) { m_commandIndex = 1; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex = 0; }	// �������{�^��������������

		if (m_commandIndex == 1) { m_arrowPosY = 890; m_colorFlag[1] = false; }
		if (m_commandIndex == 0) { m_arrowPosY = 975; m_colorFlag[0] = false; }

		if (Input::IsPress(ENTER) && m_commandIndex == 1) { m_commandIndex = 2; }				// ���������R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 0) { Player::SetBattleFlag(false); }		// �ɂ���R�}���h��I��

		m_commandName[0] = "�ɂ���";
		m_commandName[1] = "��������";
		m_commandName[2] = "";
		m_commandName[3] = "";
	}
}
