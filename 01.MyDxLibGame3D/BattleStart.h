//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̐퓬�J�n�����N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleStart : public BattleStateMachine
{
public:
	BattleStart();						// �R���X�g���N�^.
	~BattleStart() override;			// �f�X�g���N�^.

	void Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene) override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	int m_waitTimer;		// ��ʂڂ������Ԍv��p.
	int gaussianScreen;		// ��ʂڂ����p�摜�i�[�p�n���h��.
	int m_arrowMoveNum;		// �R�}���h�I����̔���������p�ϐ�.
	int m_intervalNum;
};