//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"
#include "Enemy.h"
#include "Player.h"
#include "BattleEventManager.h"
#include "BoxCollider.h"
#include "WallCollider.h"

enum NormalState		// �m�[�}���C�x���g�̏�ԊǗ�.
{
	Round1,		// 1�o�g����.
	Round2,		// 2�o�g����.
	Round3,		// 3�o�g����.
	Boss,		// �{�X��.
	End
};

class PlayScene : public Scene
{
public:
	PlayScene();					// �R���X�g���N�^.
	~PlayScene() override;			// �f�X�g���N�^.

	TAG_SCENE Update() override;	// �X�V����.
	void Draw() override;			// �`�揈��.

	// ���ݍU�����Ă���L�����N�^�[���o�g���X�e�[�g�}�V���N���X����󂯎��p
	void SetAttackObjectAddress(Character* _AttackObject) { m_pCharacterAttackNow = _AttackObject; }
	// �o�g���t���O���Z�b�g����
	void SetBattleFlag(const bool& _flag) { m_battleFlag = _flag; }
	// �m�[�}���X�e�[�g���Z�b�g����
	void SetNomalState(const NormalState& _normalState) { m_normalState = _normalState; }
	// �m�[�}���X�e�[�g���Q�b�g����
	const NormalState& GetNomalState() const { return m_normalState; }

	std::vector<Character*> GetCharacterArrayAddress() { return m_pCharacter; }
	Character* GetAttackNowCharacter() { return m_pCharacterAttackNow; }
	Player* GetPlayerAddress() { return m_pPlayer; }
private:

	void EnemyCreate(NormalState num);		// �G��������.
	void NormalEvent();		// �m�[�}���C�x���g.
	void BattleEvent();		// �퓬�C�x���g.
	void NormalEventDraw();	// �m�[�}���C�x���g�`�揈��.
	void BattleEventDraw(); // �퓬�C�x���g�`�揈��.

	int m_blackWindow;		// �s����̌��ʕ����`��p�̍��g.
	int m_statusWindow;		// ���x���E�o���l�ʁE�̗͗ʂ��f���p�̍��g.
	int m_commandIndex;		// �R�}���h�I��J�ڂ̔���p�ϐ�.
	int m_enemyLevelMax;	// �G���J�E���g����G�̍ő僌�x���ۑ��p.
	int m_enemyLevelMin;	// �G���J�E���g����G�̍ŏ����x���ۑ��p.

	bool m_selectFlag;
	bool m_movieFlag;
	bool m_battleFlag;
	std::vector<Character*> m_pCharacter;
	std::vector<Enemy*> m_pEnemyArray;
	Character* m_pCharacterAttackNow;		// �U�����̃L�����N�^�[
	Player* m_pPlayer;
	WallCollider* m_pWallCollider;			// 

	BattleEventManager* m_pBattleManager;	// �o�g���Ǘ��N���X�|�C���^.

	NormalState m_normalState;				// �m�[�}���C�x���g�̏�ԊǗ�.

	VECTOR m_cameraPos;
};