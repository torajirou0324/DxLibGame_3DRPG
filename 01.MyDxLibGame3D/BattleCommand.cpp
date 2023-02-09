//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#include "BattleCommand.h"
#include "Input.h"
#include "CommandInvoker.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleCommand::BattleCommand(class PlayScene* _playScene)
	: m_selectFlag(false)
	, m_escapeFlag(false)
{
	m_pPlaySceneStorage = _playScene;
	//std::function<void(MoveCommand)> func = 
	m_pInvokerArray.push_back(new CommandInvoker("��������"));
	//m_pInvokerArray[TAG_Command::AttackCommand]->SetOnCommand(new SimpleCommand())
	m_pInvokerArray.push_back(new CommandInvoker("�܂ق�"));
	m_pInvokerArray.push_back(new CommandInvoker("��������"));
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
void BattleCommand::Init()
{
	m_selectFlag = false;
	m_escapeFlag = false;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleCommand::Update()
{
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


	//DrawArrowSide(1370, m_arrowPosY); // ���̕\��
	//DrawGraph(m_arrowPosX + m_arrowMoveNum, m_arrowPosY, m_arrowHandle[m_textFlag], TRUE);
}
