#pragma once
#include "BattleStateMachine.h"

class BattleVictory : public BattleStateMachine
{
public:
	BattleVictory();					// �R���X�g���N�^.
	~BattleVictory() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};