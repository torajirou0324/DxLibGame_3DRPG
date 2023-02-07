#pragma once
#include "BattleStateMachine.h"

class BattleDefeat : public BattleStateMachine
{
public:
	BattleDefeat();						// �R���X�g���N�^.
	~BattleDefeat() override;			// �f�X�g���N�^.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.
};