//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"

class PlayScene : public Scene
{
public:
	PlayScene();					// �R���X�g���N�^.
	~PlayScene() override;			// �f�X�g���N�^.

	TAG_SCENE Update() override;	// �X�V����.
	void Draw() override;			// �`�揈��.

private:
	void NormalEvent();
	void BattleEvent();		// �퓬�C�x���g.
	void BattleEventDraw(); // �퓬�C�x���g�`�揈��.
	void CommandEvent();	// �R�}���h�I������.

	enum BattleState		// �o�g���C�x���g�̏�ԊǗ�.
	{
		Start,				// �J�n����.
		Command,			// �R�}���h�I������.
		Comparison,			// ��r����.�i�f�����j
		AttackProcess,		// �U������.
		SpecialMoveProcess,	// ����Z����.
		PersonalEffects,	// �������̎g�p����.
		Victory,			// ��������.
		Defeat,				// �s�k����.
		Continue			// �^�[���p������.
	};

	int m_blackWindow;		// �s����̌��ʕ����`��p�̍��g.
	int m_commandWindow[2];	// �R�}���h�I�����̍��g�Ɣ��g.
	int m_statusWindow;		// ���x���E�o���l�ʁE�̗͗ʂ��f���p�̍��g.
	int m_arrowHandle[2];	// �R�}���h�I����̃��f���n���h��.
	int m_arrowPosX;		// �R�}���h�I�����X���W.
	int m_arrowPosY;		// �R�}���h�I�����Y���W.
	int m_arrowMoveNum;		// �R�}���h�I����̔���������p�ϐ�.
	int m_intervalNum;
	int m_commandIndex;		// �R�}���h�I��J�ڂ̔���p�ϐ�.

	int m_waitTimer;		// �ҋ@���ԕۑ��p�ϐ�

	int m_enemyHPMAX;

	bool m_textFlag;
	std::vector<bool> m_colorFlag;
	std::vector<std::string> m_commandName;

	class Enemy* m_pEnemy;

	BattleState m_battleState;// �o�g���C�x���g�̏�ԊǗ�.
};