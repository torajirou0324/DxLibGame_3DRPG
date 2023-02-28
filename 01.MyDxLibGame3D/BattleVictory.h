#pragma once
#include "BattleStateMachine.h"

class BattleVictory : public BattleStateMachine
{
public:
	BattleVictory(class BattleEventManager* _manager);					// �R���X�g���N�^.
	~BattleVictory() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	class BattleEventManager* m_pBattleManager;
};