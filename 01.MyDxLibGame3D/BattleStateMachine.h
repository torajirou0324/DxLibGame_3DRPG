//-----------------------------------------------------------------------------
// @brief  �o�g���X�e�[�g�̊��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <DxLib.h>

enum class TAG_BattleState		// �o�g���C�x���g�̏�ԊǗ�.
{
	Start,				// �J�n����.
	Command,			// �R�}���h�I������.
	Comparison,			// ��r����.�i�f�����j
	MoveMentStart,		// �S�L�����s������.
	MoveMentEnd,		// �S�L�����s�������ҋ@����.
	Escape,				// �����鏈��.
	Victory,			// ��������.
	Defeat,				// �s�k����.
	Continue,			// �^�[���p������.
	End					// �Ō�.
};

class BattleStateMachine
{
public:
	BattleStateMachine() {}
	virtual ~BattleStateMachine() {}

	virtual void Init() = 0;
	virtual TAG_BattleState Update() = 0;
	virtual void Draw() = 0;
};