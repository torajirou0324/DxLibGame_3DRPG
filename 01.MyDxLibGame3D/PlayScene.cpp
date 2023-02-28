//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#include "PlayScene.h"

#include <functional>
#include <DxLib.h>
#include "Input.h"
#include "Field.h"
#include "ColliderManager.h"
#include "Deamon.h"
#include "WalkAroundEnemy.h"


//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
PlayScene::PlayScene()
	: m_selectFlag(false)
	, m_movieFlag(false)
	, m_battleFlag(false)
	, m_pBattleManager(nullptr)
{
	ColliderManager::CreateInstance();

	// �v���C���[����
	m_pPlayer = new Player;
	m_pPlayer->Init();

	// �m�[�}���C�x���g�}�l�[�W���[�̏�����
	m_pNomalManager = new NormalEventManager(m_pPlayer, std::bind(&PlayScene::ChangeSetBattleEnemyCreate, this, std::placeholders::_1, std::placeholders::_2));
	m_pNomalManager->Init();

	// �o�g���}�l�[�W���[�̏�����
	m_pBattleManager = new BattleEventManager(m_pPlayer, m_pEnemyArray, std::bind(&PlayScene::ChangeSetBattleFlag, this, std::placeholders::_1));
	m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);
	
	// �J�����̃|�W�V�����Z�b�g
	m_cameraPos = VGet(0.0f, 60.0f, -50.0f);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
PlayScene::~PlayScene()
{
	if (m_pBattleManager != nullptr)
	{
		delete m_pBattleManager;
		m_pBattleManager = nullptr;
	}
	if (m_pNomalManager != nullptr)
	{
		delete m_pNomalManager;
		m_pNomalManager = nullptr;
	}

	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		if (m_pEnemyArray[i] != nullptr)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
	}
	m_pEnemyArray.clear();
	delete m_pPlayer;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_SCENE PlayScene::Update()
{
	if (m_battleFlag)
	{
		// �o�g���J�������Z�b�g
		SetCameraPositionAndTarget_UpVecY(m_cameraPos, VGet(0.0f, 20.0f, 20.0f));
		m_pBattleManager->Update();
	}
	else
	{
		m_pNomalManager->Update();
	}

	if (m_battleFlag == false && m_pPlayer->GetDeathFlag())
	{
		return TAG_SCENE::TAG_TITLE;
	}
	return TAG_SCENE::TAG_NONE;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::Draw()
{
	// �f�o�b�O�p������{�ϐ��l�`��
	printfDx("PlayScene\n");

	if (m_battleFlag)
	{
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			m_pEnemyArray[i]->Draw();
		}
		m_pBattleManager->Draw();
	}
	else
	{
		m_pNomalManager->Draw();
	}
}

void PlayScene::ChangeSetBattleFlag(const bool& _flag)
{
	m_battleFlag = _flag;

	m_pNomalManager->Init();
}

void PlayScene::ChangeSetBattleEnemyCreate(const bool& _flag, WalkAroundEnemy* _enemy)
{
	m_battleFlag = _flag;

	// ��x�O�̓G�����.
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		if (m_pEnemyArray[i] != nullptr)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
	}
	m_pEnemyArray.clear();

	// �G�̐�������.
	auto CreateLevel = _enemy->GetLevel();
	auto CreateNum = _enemy->GetEnemyNum();

	for (int i = 0; i < CreateNum; i++)
	{
		auto obj = new Deamon;
		obj->Init("�f�[����", CreateLevel, VGet(0.0f + (i * 10.0f), 1.0f, 10.0f));
		obj->SetAttackObjectAddress(m_pPlayer);
		m_pEnemyArray.push_back(obj);
	}

	m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);
}