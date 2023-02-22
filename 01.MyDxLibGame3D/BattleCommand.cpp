//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#include "BattleCommand.h"
#include "Input.h"
#include "PlayScene.h"
#include "ArrowSymbol.h"
#include "SimpleCommand.h"
#include "SkillCommand.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleCommand::BattleCommand(class PlayScene* _playScene)
	: m_commandState(TAG_CommandState::TAG_isPlay)
{
	m_pPlaySceneStorage = _playScene;
	auto player = m_pPlaySceneStorage->GetPlayerAddress();
	auto skillarray = player->GetSKILL();
	std::function<void(SKILL)> skillfunc = std::bind(&Player::SetUseSkill, player, std::placeholders::_1);
	// �R�}���h�I���̑J�ڕK�v������
	for (int i = 0; i < TAG_CommandState::TAG_Max; i++)
	{
		m_pCommandManager.push_back(new BattleCommandManager);
	}
	// �퓬�ɂ��邩���Ȃ����I��p�N���X����
	m_pCommandManager[TAG_CommandState::TAG_isPlay]->SetCommand(new SimpleCommand("�ɂ���", TAG_CommandState::TAG_Escape, TAG_CommandState::TAG_None));
	m_pCommandManager[TAG_CommandState::TAG_isPlay]->SetCommand(new SimpleCommand("��������", TAG_CommandState::TAG_isMoveType, TAG_CommandState::TAG_None));
	// �s���̃^�C�v�i�܂ق����g���������ɂ������������邩�j
	m_pCommandManager[TAG_CommandState::TAG_isMoveType]->SetCommand(new SimpleCommand("�܂ق�", TAG_CommandState::TAG_isMagicSkill, TAG_CommandState::TAG_isPlay));
	m_pCommandManager[TAG_CommandState::TAG_isMoveType]->SetCommand(new SimpleCommand("��������",TAG_CommandState::TAG_isAttackSkill, TAG_CommandState::TAG_isPlay));
	// �U���i�[�p
	for (int i = 0; i < 4; i++)
	{
		SKILL skill = skillarray[i];
		m_pCommandManager[TAG_CommandState::TAG_isAttackSkill]->SetCommand(new SkillCommand(skillfunc, skill,TAG_CommandState::TAG_ActionCompleted, TAG_CommandState::TAG_isMoveType));
		m_pCommandManager[TAG_CommandState::TAG_isMagicSkill]->SetCommand(new SkillCommand(skillfunc, skill, TAG_CommandState::TAG_ActionCompleted, TAG_CommandState::TAG_isMoveType));
	}
	
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleCommand::~BattleCommand()
{
	for (int i = 0; i < TAG_CommandState::TAG_Max; i++)
	{
		delete m_pCommandManager[i];
		m_pCommandManager[i] = nullptr;
	}
	m_pCommandManager.clear();
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleCommand::Init()
{
	m_commandState = TAG_CommandState::TAG_isPlay;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleCommand::Update()
{
	auto tag = m_pCommandManager[m_commandState]->Update();
	
	if (tag != TAG_CommandState::TAG_None)
	{
		m_commandState = tag;
	}

	// ������R�}���h���I�����ꂽ����ESCAPE������
	if (tag == TAG_CommandState::TAG_Escape)
	{
		return TAG_BattleState::BattleEscapeProcess;
	}
	// �퓬�R�}���h���I�����ꂽ���ߑf������r������
    if (tag == TAG_CommandState::TAG_ActionCompleted)
    {
		return TAG_BattleState::MoveMentStart;
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
	m_pCommandManager[m_commandState]->Draw();
}
