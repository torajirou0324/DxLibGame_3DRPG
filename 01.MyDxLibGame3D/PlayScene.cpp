//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#include "PlayScene.h"
#include <DxLib.h>
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

	m_commandName.push_back("�ɂ���");
	m_commandName.push_back("��������");
	m_commandName.push_back("");
	m_commandName.push_back("");
	
	m_battleState = Start;

	m_pCharacterAttackNow = nullptr;
	m_pPlayer = new Player;
	m_pPlayer->Init();
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
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
// @brief  �X�V����.
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
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::Draw()
{
	// �f�o�b�O�p������{�ϐ��l�`��
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
	// �G�̗v�f���폜
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		delete m_pEnemyArray[i];
		m_pEnemyArray[i] = nullptr;
	}
	m_pEnemyArray.clear();
	m_battleState = Start;

	// �G�𐶐�
	switch (m_normalState)
	{
	case PlayScene::Round1:
		for (int i = 0; i < m_normalState + 1; i++)
		{
			int level = GetRand(m_enemyLevelMax) + 1;
			auto obj = new Deamon;
			obj->Init("�f�[����", level);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
		break;
	case PlayScene::Round2:
		for (int i = 0; i < m_normalState + 1; i++)
		{
			int level = GetRand(m_enemyLevelMax) + 1;
			auto obj = new Deamon;
			obj->Init("�f�[����", level);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
		break;
	case PlayScene::Round3:
		for (int i = 0; i < m_normalState + 1; i++)
		{
			int level = GetRand(m_enemyLevelMax) + 1;
			auto obj = new Deamon;
			obj->Init("�f�[����", level);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
		break;
	case PlayScene::Boss:
	{
		auto obj = new Deamon;
		obj->Init("�f�[����", 15);
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
			m_commandIndex = 0;
			m_pCharacter.push_back(m_pPlayer);
			for (int i = 0; i < m_pEnemyArray.size(); i++)
			{
				m_pCharacter.push_back(m_pEnemyArray[i]);
			}
		}
		break;
	case PlayScene::Command:		// �R�}���h�I������
		m_arrowPosX = 1370;
		m_textFlag = false;
		if (m_pPlayer->GetDeathFlag())
		{
			m_battleState = Defeat;
		}
		CommandEvent();
		break;
	case PlayScene::Comparison:		// �f������r����
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
			if (!m_pCharacter[i]->GetActionFlag() && !m_pCharacter[i]->GetDeathFlag())	// �s���ς݂��ǂ�������
			{
				m_pCharacter[i]->Attack();
				m_pCharacter[i]->Action();			// �U���������Ƃ�m�点��
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
			if (!m_pCharacter[i]->GetDeathFlag())				// ����ł��邩�ǂ���
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
	case PlayScene::Victory:		// ��������
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
	case PlayScene::Defeat:			// �s�k����
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
	case PlayScene::Escape:			// �����鏈��
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
	case PlayScene::Continue:		// �^�[���p������
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
		auto& playerStatus = m_pPlayer->GetAllStatus();
		float berdif = static_cast<float>(playerStatus.HP) / m_pPlayer->GetHPMAX();
		auto ber = 350 * berdif;
		DrawFormatString(50, 786, GetColor(255, 255, 255), "Lv.%d�@�@�@�L�c�L�@�C�`�J", playerStatus.LV);
		DrawBox(50, 870, 50 + ber, 910, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 868, 402, 912, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 883, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, m_pPlayer->GetHPMAX());
		berdif = static_cast<float>(playerStatus.EXP) / m_pPlayer->GetEXPMAX();
		ber = 350 * berdif;
		DrawBox(50, 920, 50 + ber, 960, GetColor(0, 255, 255), TRUE);
		DrawBox(48, 918, 402, 962, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 927, GetColor(255, 255, 255), "%d/%d", playerStatus.EXP, m_pPlayer->GetEXPMAX());
	}

	// �G�l�~�[�̃X�e�[�^�X�\���p�̍��g
	{
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			int addNum = i + 1;
			DrawGraph(1920 - (520 * addNum), 0, m_statusWindow, TRUE);
			auto& enemyStatus = m_pEnemyArray[i]->GetAllStatus();
			float HPberdif = static_cast<float>(enemyStatus.HP) / m_pEnemyArray[i]->GetHPMAX();
			auto HPber = 350 * HPberdif;

			DrawFormatString(1920 - (520 * addNum) + 50, 36, GetColor(255, 255, 255), "Lv.%d�@�@%s", enemyStatus.LV, m_pEnemyArray[i]->GetName().c_str());
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
			DrawFormatString(650, 800 + 60 * i, white, "%s�����ꂽ�B", m_pEnemyArray[i]->GetName().c_str());
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
		DrawFormatString(650, 800, white, "�R�}���h�I��...");
		break;
	case PlayScene::Comparison:
		break;
	case PlayScene::AttackProcess:
		DrawLine(1100, 0, 1500, 1080, 10 * (120 - m_waitTimer));
		DrawFormatString(650, 800, white, "Lv%d:%s����������",m_pCharacterAttackNow->GetAllStatus().LV, m_pCharacterAttackNow->GetName().c_str());
		break;
	case PlayScene::Victory:
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			DrawFormatString(650, 800 + 60 * i, white, "%s����������", m_pEnemyArray[i]->GetName().c_str());
		}
		break;
	case PlayScene::Defeat:
		DrawFormatString(650, 800, white, "�L�c�L�@�C�`�J�͓|�ꂽ");
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
		m_commandName[i] = "";
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
	if (m_commandIndex > 5 && m_commandIndex < 10)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// �������{�^��������������

		if (m_commandIndex < 6) { m_commandIndex = 6; }
		if (m_commandIndex > 6 + m_pEnemyArray.size()) { m_commandIndex = 6 + m_pEnemyArray.size(); }

		// ���̍��W�ړ�����
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

		if (Input::IsPress(ENTER) && m_commandIndex == 1) { m_commandIndex = 2; }		// ���������R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 0) { m_battleState = Escape; }		// �ɂ���R�}���h��I��

		m_commandName[0] = "�ɂ���";
		m_commandName[1] = "��������";
		m_commandName[2] = "";
		m_commandName[3] = "";
	}
}
