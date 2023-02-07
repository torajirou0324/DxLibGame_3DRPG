//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̃R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleCommand : public BattleStateMachine
{
public:
	BattleCommand();					// �R���X�g���N�^.
	~BattleCommand() override;			// �f�X�g���N�^.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	void CommandSelectProcess();		// �o�g���C�x���g�̃R�}���h�I������.

	int m_commandIndex;
	int m_enemyAllNum;		// �G�̑���.
	int m_commandWindow[2];	// �R�}���h�I�����̍��g�Ɣ��g.
	int m_arrowPosY;		// ����Y���W.
	int m_arrowMoveNum;		// �R�}���h�I����̔���������p�ϐ�.
	int m_intervalNum;

	bool m_escapeFlag;		// �R�}���h�������������������p
	bool m_selectFlag;		// �R�}���h�I���ς�����p.
	bool m_colorFlag[4];	// �R�}���h�p�摜�̔�������p�z��.

	std::string m_commandName[4];	// �R�}���h�ɕ\�����镶��.
};