//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#pragma once
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

	int m_blackWindow;		// �s����̌��ʕ����`��p�̍��g.
	int m_commandWindow[2];	// �R�}���h�I�����̍��g.
	int m_statusWindow;		// ���x���E�o���l�ʁE�̗͗ʂ��f���p�̍��g.
	int m_arrowHandle;		// �R�}���h�I����̃��f���n���h��.
	int m_arrowPosX;		// �R�}���h�I�����X���W.
	int m_arrowPosY;		// �R�}���h�I�����Y���W.
	int m_randomNumber;		// �����i�[�p�̕ϐ�.
	int m_EncountInterval;	// �G�Ƃ̃G���J�E���g�Ԋu����p�̕ϐ�.
	int m_commandIndex;		// �R�}���h�I��J�ڂ̔���p�ϐ�.

	//int m_playerHPMAX;
	int m_enemyHPMAX;
	class Enemy* m_pEnemy;
};