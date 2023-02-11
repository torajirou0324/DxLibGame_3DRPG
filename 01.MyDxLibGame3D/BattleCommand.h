//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"
#include "CommandInvoker.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand(class PlayScene* _playScene);		// �R���X�g���N�^.
	~BattleCommand() override;						// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	bool m_escapeFlag;		// �R�}���h�������������������p.
	bool m_battleFlag;		// �R�}���h����������������������p.

	TAG_Command m_commandState;
	std::vector<CommandInvoker*> m_pInvokerArray;
};