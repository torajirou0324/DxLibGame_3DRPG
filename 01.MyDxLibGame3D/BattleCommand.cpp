//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#include "BattleCommand.h"
#include "Input.h"
#include "ArrowSymbol.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleCommand::BattleCommand()
	: m_arrowPosY(0)
	, m_selectFlag(false)
	, m_escapeFlag(false)
	, m_arrowMoveNum(0)		// �R�}���h�I����̔���������p�ϐ�.
	, m_intervalNum(0)
{
	m_commandWindow[0] = AssetManager::UseImage(AssetManager::CommandWindowWhite);
	m_commandWindow[1] = AssetManager::UseImage(AssetManager::CommandWindowBlack);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleCommand::~BattleCommand()
{
}

//-----------------------------------------------------------------------------
// @brief  ����������.
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
// @brief  �X�V����.
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
	// ������R�}���h���I�����ꂽ����ESCAPE������
	if (m_escapeFlag)
	{
		return TAG_BattleState::BattleEscapeProcess;
	}
	// �퓬�R�}���h���I�����ꂽ���ߑf������r������
    if (m_selectFlag)
    {
        return TAG_BattleState::Comparison;
    }

    return TAG_BattleState::None;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleCommand::Draw()
{
	DrawFormatString(650, 800, GetColor(255, 255, 255), "�R�}���h�I��...");

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

	DrawArrowSide(1370 + m_arrowMoveNum, m_arrowPosY); // ���̕\��
	//DrawGraph(m_arrowPosX + m_arrowMoveNum, m_arrowPosY, m_arrowHandle[m_textFlag], TRUE);
}

//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I������.
//-----------------------------------------------------------------------------
void BattleCommand::CommandSelectProcess()
{
	for (int i = 0; i < 4; i++)
	{
		m_colorFlag[i] = true;
		m_commandName[i] = "";
	}

	// �R�}���h�F���������̂��������ڕW�I������
	if (m_commandIndex > 5 && m_commandIndex < 10)
	{
		if (Input::IsPress(UP)) { m_commandIndex++; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex--; }		// �������{�^��������������

		if (m_commandIndex < 6) { m_commandIndex = 6; }
		if (m_commandIndex > 6 + m_enemyAllNum) { m_commandIndex = 6 + m_enemyAllNum; }

		for (int i = 0; i < 4; i++)
		{
			if (m_commandIndex == 6 + i)
			{
				// ���̍��W�ړ�����
				m_arrowPosY = 975 - (85 * i); m_colorFlag[i] = false;

				if (i < 1)
				{
					if (Input::IsPress(ENTER) && m_commandIndex == 6) { m_commandIndex = 5;  return; }		// ���ǂ�R�}���h��I��
				}
				else if (Input::IsPress(ENTER) && !m_pCharacter[i]->GetDeathFlag())
				{
					// �v���C���[�̍U���ڕW�ɓG����
					m_pCharacter[0]->SetAttackObjectAddress(m_pCharacter[i]);
					m_selectFlag = true;
				}
			}

			if (i > 0 && i <= m_enemyAllNum)
			{
				m_commandName[i] = m_pCharacter[i]->GetName();
			}
		}
		m_commandName[0] = "���ǂ�";
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

		if (Input::IsPress(ENTER) && m_commandIndex == 5) { m_commandIndex = 9; }				// ���������R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 4) { m_commandIndex = 9; }				// �Ƃ������I��
		if (Input::IsPress(ENTER) && m_commandIndex == 3 /*&& m_healFlag*/)	// �����ӂ���I��
		{
			//m_pPlayer->HPHeal();
			//m_healFlag = false;
			m_selectFlag = true;
		}
		if (Input::IsPress(ENTER) && m_commandIndex == 2) { m_commandIndex = 1; return; }		// ���ǂ�R�}���h��I��

		m_commandName[0] = "���ǂ�";
		m_commandName[2] = "�Ƃ�����";
		m_commandName[3] = "��������";
		//if (m_healFlag)
		//{
		//	m_commandName[1] = "�����ӂ���";
		//}
		//else
		//{
			m_commandName[1] = "�����ӂ�";
		//}
	}
	// ���������E�ɂ��邩�̑I������
	if (m_commandIndex < 2)
	{
		if (Input::IsPress(UP)) { m_commandIndex = 1; }		// ������{�^��������������
		if (Input::IsPress(DOWN)) { m_commandIndex = 0; }	// �������{�^��������������

		if (m_commandIndex == 1) { m_arrowPosY = 890; m_colorFlag[1] = false; }
		if (m_commandIndex == 0) { m_arrowPosY = 975; m_colorFlag[0] = false; }

		if (Input::IsPress(ENTER) && m_commandIndex == 1) { m_commandIndex = 5; }		// ���������R�}���h��I��
		if (Input::IsPress(ENTER) && m_commandIndex == 0) { m_escapeFlag = true; }	// �ɂ���R�}���h��I��

		m_commandName[0] = "�ɂ���";
		m_commandName[1] = "��������";
		m_commandName[2] = "�X�e�[�^�X";
	}
}
