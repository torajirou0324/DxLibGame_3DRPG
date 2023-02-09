//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̐퓬�J�n�����N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "BattleStateMachine.h"

class BattleStart : public BattleStateMachine
{
public:
	BattleStart(class PlayScene* _playScene);						// �R���X�g���N�^.
	~BattleStart() override;			// �f�X�g���N�^.

	void Init() override;				// ����������.
	TAG_BattleState Update() override;	// �X�V����.
	void Draw() override;				// �`�揈��.

private:
	int m_waitTimer;		// ��ʂڂ������Ԍv��p.
	int gaussianScreen;		// ��ʂڂ����p�摜�i�[�p�n���h��.
};