//-----------------------------------------------------------------------------
// @brief  �^�[���p�������N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleContinue : public BattleStateMachine
{
public:
	BattleContinue();					// �R���X�g���N�^.
	~BattleContinue() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};