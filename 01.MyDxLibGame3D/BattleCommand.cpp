//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#include "BattleCommand.h"
#include "Input.h"
#include "PlayScene.h"
#include "ArrowSymbol.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleCommand::BattleCommand(class PlayScene* _playScene)
	: m_battleFlag(false)
	, m_escapeFlag(false)
	, m_commandState(TAG_Command::AttackCommand)
{
	m_pPlaySceneStorage = _playScene;
	auto player = m_pPlaySceneStorage->GetPlayerAddress();
	auto skillarray = player->GetSKILL();
	m_pInvokerArray.push_back(new CommandInvoker("�܂ق�"));
	m_pInvokerArray.push_back(new CommandInvoker("��������"));
	for (int i = 0; i < 4; i++)
	{
		m_pInvokerArray[0]->SetOnCommand(new SimpleCommand(player, skillarray[i]));
		m_pInvokerArray[1]->SetOnCommand(new SimpleCommand(player, skillarray[i]));
	}

	auto func = std::bind(&Player::Move());
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleCommand::~BattleCommand()
{
	for (const auto& it : m_pInvokerArray)
	{
		if (it != nullptr)
		{
			delete it;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleCommand::Init()
{
	m_battleFlag = false;
	m_escapeFlag = false;
	m_commandState = TAG_Command::AttackCommand;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleCommand::Update()
{
	if (m_battleFlag)
	{
		for (int i = 0; i < m_pInvokerArray.size(); i++)
		{
			m_pInvokerArray[i]->m_display = false;
		}

		m_pInvokerArray[m_commandState]->Update();
		if (m_pInvokerArray[m_commandState]->GetDicideFlag())
		{
			return TAG_BattleState::None;
		}
		if (Input::IsPress(UP))
		{
			m_commandState = TAG_Command::AttackCommand;
		}
		if (Input::IsPress(DOWN))
		{
			m_commandState = TAG_Command::IntelligenceCommand;
		}
		if (Input::IsPress(BACK))
		{
			m_battleFlag = false;
		}
		return TAG_BattleState::None;
	}


	if (Input::IsPress(UP))
	{
		m_escapeFlag = false;
	}
	if (Input::IsPress(DOWN))
	{
		m_escapeFlag = true;
	}
	// ������R�}���h���I�����ꂽ����ESCAPE������
	if (m_escapeFlag && Input::IsPress(ENTER))
	{
		return TAG_BattleState::BattleEscapeProcess;
	}
	// �퓬�R�}���h���I�����ꂽ���ߑf������r������
    if (!m_escapeFlag && Input::IsPress(ENTER))
    {
		m_battleFlag = true;
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

	if (m_battleFlag)
	{
		for (int i = 0; i < m_pInvokerArray.size(); i++)
		{
			m_pInvokerArray[i]->Draw(975 - (80 * i));
		}
	}
	else
	{
		if (m_escapeFlag)
		{
			DrawGraph(1400, 975, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
			DrawFormatString(1480, 975 + 10, GetColor(0, 0, 0), "�ɂ���");
			DrawGraph(1400, 895, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
			DrawFormatString(1480, 895 + 10, GetColor(255, 255, 255), "��������");

			DrawArrowSide(1370, 990);
		}
		else
		{
			DrawGraph(1400, 975, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
			DrawFormatString(1480, 975 + 10, GetColor(255, 255, 255), "�ɂ���");
			DrawGraph(1400, 895, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
			DrawFormatString(1480, 895 + 10, GetColor(0, 0, 0), "��������");

			DrawArrowSide(1370, 910);
		}
	}

}
