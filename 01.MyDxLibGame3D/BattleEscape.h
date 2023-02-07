#pragma once
#include "BattleStateMachine.h"

class BattleEscape : public BattleStateMachine
{
public:
	BattleEscape();						// �R���X�g���N�^.
	~BattleEscape() override;			// �f�X�g���N�^.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};