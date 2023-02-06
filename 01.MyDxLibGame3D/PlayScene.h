//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"
#include "Enemy.h"
#include "Player.h"

class PlayScene : public Scene
{
public:
	PlayScene();					// �R���X�g���N�^.
	~PlayScene() override;			// �f�X�g���N�^.

	TAG_SCENE Update() override;	// �X�V����.
	void Draw() override;			// �`�揈��.

private:
	enum NormalState		// �m�[�}���C�x���g�̏�ԊǗ�.
	{
		Round1,		// 1�o�g����.
		Round2,		// 2�o�g����.
		Round3,		// 3�o�g����.
		Boss,		// �{�X��.
		End
	};

	enum BattleState		// �o�g���C�x���g�̏�ԊǗ�.
	{
		Start,				// �J�n����.
		Command,			// �R�}���h�I������.
		Comparison,			// ��r����.�i�f�����j
		MoveMent,			// �s��.
		AttackProcess,		// �U������.
		SpecialMoveProcess,	// ����Z����.
		PersonalEffects,	// �������̎g�p����.
		Victory,			// ��������.
		Defeat,				// �s�k����.
		Escape,				// �����鏈��.
		Continue			// �^�[���p������.
	};

	void EnemyCreate(NormalState num);		// �G��������.
	void NormalEvent();		// �m�[�}���C�x���g.
	void BattleEvent();		// �퓬�C�x���g.
	void NormalEventDraw();	// �m�[�}���C�x���g�`�揈��.
	void BattleEventDraw(); // �퓬�C�x���g�`�揈��.
	void CommandEvent();	// �R�}���h�I������.

	int m_blackWindow;		// �s����̌��ʕ����`��p�̍��g.
	int m_commandWindow[2];	// �R�}���h�I�����̍��g�Ɣ��g.
	int m_statusWindow;		// ���x���E�o���l�ʁE�̗͗ʂ��f���p�̍��g.
	int m_arrowHandle[2];	// �R�}���h�I����̃��f���n���h��.
	int m_arrowPosX;		// �R�}���h�I�����X���W.
	int m_arrowPosY;		// �R�}���h�I�����Y���W.
	int m_arrowMoveNum;		// �R�}���h�I����̔���������p�ϐ�.
	int m_intervalNum;
	int m_commandIndex;		// �R�}���h�I��J�ڂ̔���p�ϐ�.
	int m_enemyLevelMax;	// �G���J�E���g����G�̍ő僌�x���ۑ��p.
	int m_enemyLevelMin;	// �G���J�E���g����G�̍ŏ����x���ۑ��p.
	int gaussianScreen;		// ��ʂڂ����p�摜�i�[�p�n���h��.

	int m_waitTimer;		// �ҋ@���ԕۑ��p�ϐ�.

	bool m_textFlag;
	bool m_selectFlag;
	bool m_movieFlag;
	bool m_battleFlag;
	bool m_enemyDeadFlag;
	bool m_healFlag;		// �ꎞ�I�ȉ񕜔���p.
	std::vector<bool> m_colorFlag;
	std::vector<std::string> m_commandName;
	std::vector<Character*> m_pCharacter;
	std::vector<Enemy*> m_pEnemyArray;
	Character* m_pCharacterAttackNow;		// �U�����̃L�����N�^�[
	Player* m_pPlayer;

	NormalState m_normalState;				// �m�[�}���C�x���g�̏�ԊǗ�.
	BattleState m_battleState;				// �o�g���C�x���g�̏�ԊǗ�.

	VECTOR m_cameraPos;
};