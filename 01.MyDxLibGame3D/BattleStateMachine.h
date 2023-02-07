//-----------------------------------------------------------------------------
// @brief  �o�g���X�e�[�g�̊��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <DxLib.h>
#include <string>
#include "Character.h"

enum TAG_BattleState	// �o�g���C�x���g�̏�ԊǗ�.
{
	Start,				// �J�n����.
	Command,			// �R�}���h�I������.
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
	virtual ~BattleStateMachine() {}

	virtual void Init(std::vector<Character*>& character, Character*& attackNowCharacter, class PlayScene* playScene) = 0;
	virtual TAG_BattleState Update() = 0;
	virtual void Draw() = 0;

protected:
	std::vector<Character*> m_pCharacter;	// �퓬���̃L�����N�^�[�̔z��
	Character* m_pCharacterAttackNow;
	class PlayScene* m_pPlayScene;		// �U�����̃L�����N�^�[
};