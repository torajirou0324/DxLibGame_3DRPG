#pragma once
#include "BattleStateMachine.h"

class BattleDefeat : public BattleStateMachine
{
public:
	BattleDefeat(class BattleEventManager* _manager);						// �R���X�g���N�^.
	~BattleDefeat() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	class BattleEventManager* m_pBattleManager;
};