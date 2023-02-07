#pragma once
#include "BattleStateMachine.h"

class BattleVictory : public BattleStateMachine
{
public:
	BattleVictory();					// �R���X�g���N�^.
	~BattleVictory() override;			// �f�X�g���N�^.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};