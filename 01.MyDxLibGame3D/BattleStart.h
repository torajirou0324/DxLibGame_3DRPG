#pragma once
#include "BattleStateMachine.h"

class BattleStart : public BattleStateMachine
{
public:
	BattleStart();						// �R���X�g���N�^.
	~BattleStart() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};