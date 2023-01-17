//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#include "PlayScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Enemy.h"
#include "Field.h"
#include "Input.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
PlayScene::PlayScene()
	: m_arrowPosX(900)
	, m_arrowPosY(800)
	, m_randomNumber(0)
	, m_EncountInterval(0)
	, m_commandIndex(0)
{
	m_pEnemy = new Enemy;
	m_playerHPMAX = Player::GetAllStatus().HP;
	m_enemyHPMAX = m_pEnemy->GetAllStatus().HP;

	m_blackWindow = LoadGraph("data/comand/BlackWindow.png");
	m_statusWindow = LoadGraph("data/comand/StatusWindow.png");
	m_arrowHandle = LoadGraph("data/comand/arrow.png");
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	delete m_pEnemy;

	DeleteGraph(m_blackWindow);
	DeleteGraph(m_statusWindow);
	DeleteGraph(m_arrowHandle);
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
			m_EncountInterval++;
		}

		if (m_EncountInterval > 180)
		{
			m_randomNumber = GetRand(2);
			if (m_randomNumber == 0)
			{
				Player::SetBattleFlag(true);
			}
			m_EncountInterval = 0;
		}
	}
	Player::Update();

	return TAG_SCENE::TAG_NONE;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::Draw()
{
	// �f�o�b�O�p������{�ϐ��l�`��
	//printfDx("PlayScene\n");
	//printfDx("%d\n", m_randomNumber);
	//printfDx("%d\n", m_EncountInterval);
	Field::DrawCall();
	Player::DrawCall();
	BattleEventDraw();
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
		// ���������A�j���[�V�������I������������
		if (Player::GetAnimTime() >= Player::GetAnimTotalTime())
		{
			m_commandIndex = 0;
			// ���������A�j���[�V�������I�������̂Ŏ��̏����Ɉڂ�
			auto playerATKDamage = Player::GetAllStatus().ATK;
			auto& enemyHP = m_pEnemy->GetAllStatus();
			Status resultEnemyStatus = enemyHP;
			resultEnemyStatus.HP = enemyHP.HP - playerATKDamage;
			if (resultEnemyStatus.HP < 0) 
			{ 
				resultEnemyStatus.HP = 0;
				m_commandIndex = 15;
			}
			m_pEnemy->SetAllStatus(resultEnemyStatus);
			Player::SetAnimType(Idle);
		}
	}

	// ���ǂ�E���������E�������́E�ւ񂩂킴�̑I������
	if (m_commandIndex > 1 && m_commandIndex < 6)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// �������{�^��������������

		if (m_commandIndex < 2) { m_commandIndex = 2; }
		if (m_commandIndex > 5) { m_commandIndex = 5; }

		// ���̍��W�ړ�����
		if (m_commandIndex == 2) { m_arrowPosX = 900; m_arrowPosY = 930; }
		if (m_commandIndex == 3) { m_arrowPosX = 900; m_arrowPosY = 800; }
		if (m_commandIndex == 4) { m_arrowPosX = 1400; m_arrowPosY = 930; }
		if (m_commandIndex == 5) { m_arrowPosX = 1400; m_arrowPosY = 800; }

		if (Input::IsPress(ENTER) && m_commandIndex == 2) { m_commandIndex = 0; }		// ���ǂ�R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 3) { m_commandIndex = 6; Player::SetAnimType(Attack); }	// ���������R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 4) { m_commandIndex = 7; }		// �ւ񂩂킴��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 5) { m_commandIndex = 11; }		// �������̂�I��
	}
	// ���������E�ɂ��邩�̑I������
	else if (m_commandIndex < 2)
	{
		if (Input::IsPress(UP)) { m_commandIndex = 0; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex = 1; }	// �������{�^��������������

		if(m_commandIndex == 0) { m_arrowPosY = 800; }
		if(m_commandIndex == 1) { m_arrowPosY = 930; }

		if (Input::IsPress(ENTER) && m_commandIndex == 0) { m_commandIndex = 2; }				// ���������R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 1) { Player::SetBattleFlag(false); }		// �ɂ���R�}���h��I��
	}

	// �G��|�������U���g����
	if (m_commandIndex == 15)
	{
		m_EncountInterval++;
		if (m_EncountInterval > 180)
		{
			Player::SetBattleFlag(false);
			m_commandIndex = 0;
			m_EncountInterval = 0;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̕`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::BattleEventDraw()
{
	if (Player::GetBattleFlag())
	{
		// �v���C���[�̃X�e�[�^�X�\���p�̍��g
		SetFontSize(40);
		DrawGraph(0, 834, m_statusWindow, TRUE);
		auto& playerStatus = Player::GetAllStatus();
		DrawFormatString(50, 870, GetColor(255, 255, 255), "Lv.%d", playerStatus.LV);
		DrawBox(50, 980, 400, 1020, GetColor(0, 255, 0), TRUE);
		DrawBox(50, 980, 400, 1020, GetColor(255, 255, 255), FALSE);
		DrawFormatString(280, 980, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, m_playerHPMAX);

		// �G�l�~�[�̃X�e�[�^�X�\���p�̍��g
		DrawGraph(1400, 0, m_statusWindow, TRUE);
		auto& enemyStatus = m_pEnemy->GetAllStatus();
		float HPberdif = static_cast<float>(enemyStatus.HP) / m_enemyHPMAX;
		auto HPber = 350 * HPberdif;

		DrawFormatString(1450, 36, GetColor(255, 255, 255), "Lv.%d", enemyStatus.LV);
		DrawBox(1450, 140, 1450 + HPber, 180, GetColor(0, 255, 0), TRUE);
		DrawBox(1450, 140, 1800, 180, GetColor(255, 255, 255), FALSE);
		DrawFormatString(1680, 140, GetColor(255, 255, 255), "%d/%d", enemyStatus.HP, m_enemyHPMAX);
		SetFontSize(64);

		if (m_commandIndex < 2)
		{
			DrawGraph(840, 718, m_blackWindow, TRUE);					// �����o���E�B���h�E�̕\��
			DrawGraph(m_arrowPosX, m_arrowPosY, m_arrowHandle, TRUE);	// ���̕\��

			DrawFormatString(1000, 800, GetColor(255, 255, 255), "��������");
			DrawFormatString(1000, 930, GetColor(255, 255, 255), "�ɂ���");
		}
		
		if (m_commandIndex > 1 && m_commandIndex < 6)
		{
			DrawGraph(840, 718, m_blackWindow, TRUE);					// �����o���E�B���h�E�̕\��
			DrawGraph(m_arrowPosX, m_arrowPosY, m_arrowHandle, TRUE);	// ���̕\��

			DrawFormatString(1000, 800, GetColor(255, 255, 255), "��������");
			DrawFormatString(1500, 800, GetColor(255, 255, 255), "��������");
			DrawFormatString(1500, 930, GetColor(255, 255, 255), "�ւ񂩂킴");
			DrawFormatString(1000, 930, GetColor(255, 255, 255), "���ǂ�");
		}

		if (m_commandIndex == 6)
		{
			DrawGraph(840, 718, m_blackWindow, TRUE);					// �����o���E�B���h�E�̕\��
			DrawFormatString(1000, 800, GetColor(255, 255, 255), "�G�l�~�[��%d�̂�������",Player::GetAllStatus().ATK);
		}

		if (m_commandIndex == 15)
		{
			DrawGraph(840, 718, m_blackWindow, TRUE);					// �����o���E�B���h�E�̕\��
			DrawFormatString(1000, 800, GetColor(255, 255, 255), "�G�l�~�[����������");
		}
	}
}
