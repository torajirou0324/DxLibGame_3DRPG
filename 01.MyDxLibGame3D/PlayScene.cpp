//-----------------------------------------------------------------------------
// @brief  �v���C�V�[���N���X.
//-----------------------------------------------------------------------------
#include "PlayScene.h"
#include <functional>
#include <DxLib.h>
#include "Deamon.h"
#include "Field.h"
#include "Input.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
PlayScene::PlayScene()
	: m_enemyLevelMax(2)
	, m_enemyLevelMin(1)
	, m_selectFlag(false)
	, m_movieFlag(false)
	, m_battleFlag(false)
	, m_commandIndex(1)
	, m_pBattleManager(nullptr)
{
	// ���@�ƓG�̐���
	m_pCharacterAttackNow = nullptr;
	m_pPlayer = new Player;
	m_pPlayer->Init();

	auto obj = new Deamon;
	obj->Init("�f�[����1", 1, VGet(0.0f, 4.5f, 20.0f));
	obj->SetAttackObjectAddress(m_pPlayer);
	m_pEnemyArray.push_back(obj);
	m_pCharacter.push_back(m_pPlayer);
	m_pCharacter.push_back(obj);

	// �o�g���X�e�[�g�̏�����
	m_pBattleManager = new BattleEventManager(this);
	m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);

	m_normalState = Round1;
	
	// �J�����̃|�W�V�����Z�b�g
	m_cameraPos = VGet(0.0f, 60.0f, -50.0f);
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, VGet(0.0f, 20.0f, 20.0f));

	m_blackWindow = AssetManager::UseImage(AssetManager::BlackWindow);
	m_statusWindow = AssetManager::UseImage(AssetManager::StatusWindow);

	m_battleFlag = true;
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
		BattleEvent();
	}
	else
	{
		NormalEvent();
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
		BattleEventDraw();
	}
	else
	{
		NormalEventDraw();
	}
}

//-----------------------------------------------------------------------------
// @brief  �G�̐�������.
//-----------------------------------------------------------------------------
void PlayScene::EnemyCreate(NormalState num)
{
	VECTOR enemySetPosition = VGet(0.0f, 4.5f, 10.0f);	// �Z�b�g����G�l�~�[�̃|�W�V����

	// �G�𐶐�
	for (int i = 0; i < num + 1; i++)
	{
		int level = 0;	// �G�̃��x���i�[�p
		// �G�̃��x���𗐐��Ő���
		if (num == Round1)
		{
			level = GetRand(m_enemyLevelMax - 1) + m_enemyLevelMin;
		}	// �ア�̂��ł₷��
		if (num == Round2)
		{
			level = GetRand(m_enemyLevelMax) + m_enemyLevelMin; enemySetPosition.x = 20.0f + (-40.0f * i);
		}	// �G�̈ʒu����+�����x���ł₷��
		if (num == Round3)
		{
			level = GetRand(m_enemyLevelMax + 1) + m_enemyLevelMin; enemySetPosition.x = 30.0f + (-30.0f * i);
		}// �G�̈ʒu����+�����̂��ł₷��
		if (num == Boss)
		{
			level = 15; enemySetPosition.x = 30.0f + (-30.0f * i);
		}

		// �G�𐶐�
		if (i < Boss)
		{
			auto obj = new Deamon;
			obj->Init(obj->GetName() + std::to_string(i + 1), level, enemySetPosition);
			obj->SetAttackObjectAddress(m_pPlayer);
			m_pEnemyArray.push_back(obj);
		}
	}
	m_battleFlag = true;	// �퓬�J�n
}

//-----------------------------------------------------------------------------
// @brief  �m�[�}���C�x���g�̏���.
//-----------------------------------------------------------------------------
void PlayScene::NormalEvent()
{
	// ���[�r�[���
	m_pPlayer->Update();

	if (Input::IsPress(ENTER))
	{
		// �G�̗v�f���폜
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
		m_pEnemyArray.clear();
		m_pCharacter.clear();
		m_pCharacter.push_back(m_pPlayer);
		// �G����
		EnemyCreate(m_normalState);
		for (auto& it:m_pEnemyArray)
		{
			m_pCharacter.push_back(it);
		}
		m_pBattleManager->Init(m_pPlayer, m_pEnemyArray);
	}

}

//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̏���.
//-----------------------------------------------------------------------------
void PlayScene::BattleEvent()
{
	for (int i = 0; i < m_pCharacter.size(); i++)
	{
		m_pCharacter[i]->Update();
	}

	m_pBattleManager->Update();
}

//-----------------------------------------------------------------------------
// @brief  �m�[�}���C�x���g�̕`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::NormalEventDraw()
{
	printfDx("camPos x:%d y:%d z:%d\n", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);
	Field::DrawCall();
	m_pPlayer->Draw();
}

//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̕`�揈��.
//-----------------------------------------------------------------------------
void PlayScene::BattleEventDraw()
{
	Field::BattleDrawCall();

	auto white = GetColor(255, 255, 255);	// ��
	auto black = GetColor(0, 0, 0);			// ��

	DrawGraph(600, 750, m_blackWindow, TRUE);					// �����o���E�B���h�E�̕\��

	SetFontSize(30);
	// �v���C���[�̃X�e�[�^�X�\��+���g
	{
		DrawGraph(0, 750, m_statusWindow, TRUE);
		auto& playerStatus = m_pPlayer->GetAllStatus();
		float berdif = static_cast<float>(playerStatus.HP) / m_pPlayer->GetHPMAX();
		auto ber = 350 * berdif;
		DrawFormatString(50, 786, GetColor(255, 255, 255), "Lv.%d�@�@�@�L�c�L�@�C�`�J", playerStatus.LV);
		DrawBox(50, 870, 50 + ber, 910, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 868, 402, 912, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 883, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, m_pPlayer->GetHPMAX());
		berdif = static_cast<float>(playerStatus.EXP) / m_pPlayer->GetEXPMAX();
		ber = 350 * berdif;
		DrawBox(50, 920, 50 + ber, 960, GetColor(0, 255, 255), TRUE);
		DrawBox(48, 918, 402, 962, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 927, GetColor(255, 255, 255), "%d/%d", playerStatus.EXP, m_pPlayer->GetEXPMAX());
	}

	// �G�l�~�[�̃X�e�[�^�X�\��+���g
	{
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			int addNum = i + 1;
			DrawGraph(1920 - (520 * addNum), 0, m_statusWindow, TRUE);
			auto& enemyStatus = m_pEnemyArray[i]->GetAllStatus();
			float HPberdif = static_cast<float>(enemyStatus.HP) / m_pEnemyArray[i]->GetHPMAX();
			auto HPber = 350 * HPberdif;

			DrawFormatString(1920 - (520 * addNum) + 50, 36, GetColor(255, 255, 255), "Lv.%d�@�@%s", enemyStatus.LV, m_pEnemyArray[i]->GetName().c_str());
			DrawBox(1920 - (520 * addNum) + 50, 140, (1920 - (520 * addNum) + 50) + HPber, 180, GetColor(0, 255, 0), TRUE);
			DrawBox(1918 - (520 * addNum) + 50, 138, (1920 - (520 * addNum) + 50) + 352, 182, GetColor(255, 255, 255), FALSE);
			DrawFormatString(1920 - (520 * addNum) + 300, 150, GetColor(255, 255, 255), "%d/%d", enemyStatus.HP, m_pEnemyArray[i]->GetHPMAX());
		}
	}

	m_pBattleManager->Draw();
}
