#pragma once
#include "BattleStateMachine.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand();					// �R���X�g���N�^.
	~BattleCommand() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};