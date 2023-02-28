//-----------------------------------------------------------------------------
// @brief  �o�g���X�e�[�g�̊��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include <functional>
#include <DxLib.h>
#include "Player.h"
#include "Enemy.h"
#include "ArrowSymbol.h"

enum TAG_BattleState	// �o�g���C�x���g�̏�ԊǗ�.
{
	Start,				// �J�n����.
	CommandProcess,		// �R�}���h�I������.
	Comparison,			// ��r����.�i�f�����j
	MoveMentStart,		// �S�L�����s������.
	MoveMentEnd,		// �S�L�����s�������ҋ@����.
	BattleEscapeProcess,// �����鏈��.
	Victory,			// ��������.
	Defeat,				// �s�k����.
	Continue,			// �^�[���p������.
	None				// �Ō�.
};

class BattleStateMachine
{
public:
	BattleStateMachine() {}
	virtual ~BattleStateMachine() 
	{
	}

	virtual void Init() = 0;
	virtual TAG_BattleState Update() = 0;
	virtual void Draw() = 0;
};