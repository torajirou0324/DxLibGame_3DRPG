//-----------------------------------------------------------------------------
// @brief  �S�L�����s�������ҋ@�����N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleMoveMentEnd : public BattleStateMachine
{
public:
	BattleMoveMentEnd(class BattleEventManager* _manager);					// �R���X�g���N�^.
	~BattleMoveMentEnd() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	class BattleEventManager* m_pBattleManager;
};