#pragma once
#include "BattleStateMachine.h"

class BattleMoveMentStart : public BattleStateMachine
{
public:
	BattleMoveMentStart();						// �R���X�g���N�^.
	~BattleMoveMentStart() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};