//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̑f������r�����N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleComparison : public BattleStateMachine
{
public:
	BattleComparison();						// �R���X�g���N�^.
	~BattleComparison() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};