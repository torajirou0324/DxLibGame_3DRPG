//-----------------------------------------------------------------------------
// @brief  �S�L�����s�������ҋ@�����N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleMoveMentEnd : public BattleStateMachine
{
public:
	BattleMoveMentEnd();					// �R���X�g���N�^.
	~BattleMoveMentEnd() override;			// �f�X�g���N�^.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};