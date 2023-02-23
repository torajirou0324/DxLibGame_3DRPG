//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"
#include "BattleCommandManager.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand(class PlayScene* _playScene);		// �R���X�g���N�^.
	~BattleCommand() override;						// �f�X�g���N�^.

	void Init() override;				// ����������.
	void Init(class Player* _player, std::vector<class Enemy*> _enemyArray) override;
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	std::vector<BattleCommandManager*> m_pCommandManager;
	TAG_CommandState m_commandState;
};