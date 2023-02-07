//-----------------------------------------------------------------------------
// @brief  �S�L�����s���������s�N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleMoveMentStart : public BattleStateMachine
{
public:
	BattleMoveMentStart();						// �R���X�g���N�^.
	~BattleMoveMentStart() override;			// �f�X�g���N�^.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	bool m_enemyAllDeadFlag;			// �G������ł��邩����p.
	bool m_playerDeadFlag;				// ���@������ł��邩����p.
};