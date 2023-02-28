//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include "SceneBase.h"
#include "Enemy.h"
#include "Player.h"
#include "NormalEventManager.h"
#include "BattleEventManager.h"

class PlayScene : public Scene
{
public:
	PlayScene();					// �R���X�g���N�^.
	~PlayScene() override;			// �f�X�g���N�^.

	TAG_SCENE Update() override;	// �X�V����.
	void Draw() override;			// �`�揈��.

	// �o�g���t���O���Z�b�g����
	void ChangeSetBattleFlag(const bool& _flag);
	void ChangeSetBattleEnemyCreate(const bool& _flag, class WalkAroundEnemy* _enemy);
private:
	Player* m_pPlayer;
	std::vector<Enemy*> m_pEnemyArray;

	NormalEventManager* m_pNomalManager;	// �m�[�}���C�x���g�Ǘ��N���X�|�C���^.
	BattleEventManager* m_pBattleManager;	// �o�g���C�x���g�Ǘ��N���X�|�C���^.

	bool m_selectFlag;
	bool m_movieFlag;
	bool m_battleFlag;

	VECTOR m_cameraPos;
};