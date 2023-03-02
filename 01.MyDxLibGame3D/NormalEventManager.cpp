//-----------------------------------------------------------------------------
// @brief  �m�[�}���C�x���g�Ǘ��N���X.
//-----------------------------------------------------------------------------
#include "NormalEventManager.h"

#include <algorithm>
#include "Input.h"
#include "Field.h"
#include "ColliderManager.h"
#include "Player.h"
#include "Collision.h"
#include "ArrowSymbol.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
NormalEventManager::NormalEventManager(Player* _player, std::function<void(bool, class WalkAroundEnemy*)> _func)
	: m_pPlayer(_player)
	, m_func(_func)
{
	// �p�j����G�̐���
	auto obj = new WalkAroundEnemy;
	obj->Init(VGet(0.0f, 0.0f, 100.0f), 1, m_pPlayer->GetAllStatus().LV);
	m_pEnemyArray.push_back(obj);
	auto obj2 = new WalkAroundEnemy;
	obj2->Init(VGet(0.0f, 0.0f, 500.0f), 2, m_pPlayer->GetAllStatus().LV);
	m_pEnemyArray.push_back(obj2);

	// 1�ʂ̕ǂ𐶐�
	float start = -150.0f;
	float end = 150.0f;
	auto wall = new WallCollider;
	wall->Init(VGet(start, 0.0f, start), VGet(end, 0.0f, start), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall);
	m_pWallColliderArray.push_back(wall);
	auto wall2 = new WallCollider;
	wall2->Init(VGet(start, 0.0f, start), VGet(start, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall2);
	m_pWallColliderArray.push_back(wall2);
	auto wall3 = new WallCollider;
	wall3->Init(VGet(end, 0.0f, start), VGet(end, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall3);
	m_pWallColliderArray.push_back(wall3);
	auto wall4 = new WallCollider;
	wall4->Init(VGet(start, 0.0f, end), VGet(-50.0f, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall4);
	m_pWallColliderArray.push_back(wall4);
	auto wall5 = new WallCollider;
	wall5->Init(VGet(50.0f, 0.0f, end), VGet(end, 0.0f, end), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall5);
	m_pWallColliderArray.push_back(wall5);

	// �ʘH��
	auto wall6 = new WallCollider;
	wall6->Init(VGet(50.0f, 0.0f, 150.0f), VGet(50.0f, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall6);
	m_pWallColliderArray.push_back(wall6);
	auto wall7 = new WallCollider;
	wall7->Init(VGet(-50.0f, 0.0f, 150.0f), VGet(-50.0f, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall7);
	m_pWallColliderArray.push_back(wall7);

	// 2�ʂ̕ǂ𐶐�
	auto wall8 = new WallCollider;
	wall8->Init(VGet(start, 0.0f, 750.0f), VGet(end, 0.0f, 750.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall8);
	m_pWallColliderArray.push_back(wall8);
	auto wall9 = new WallCollider;
	wall9->Init(VGet(start, 0.0f, 450.0f), VGet(start, 0.0f, 750.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall9);
	m_pWallColliderArray.push_back(wall9);
	auto wall10 = new WallCollider;
	wall10->Init(VGet(end, 0.0f, 450.0f), VGet(end, 0.0f, 750.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall10);
	m_pWallColliderArray.push_back(wall10);
	auto wall11 = new WallCollider;
	wall11->Init(VGet(start, 0.0f, 450.0f), VGet(-50.0f, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall11);
	m_pWallColliderArray.push_back(wall11);
	auto wall12 = new WallCollider;
	wall12->Init(VGet(50.0f, 0.0f, 450.0f), VGet(end, 0.0f, 450.0f), 50.0f, ObjectTag::Wall);
	ColliderManager::AddColliderInfo(wall12);
	m_pWallColliderArray.push_back(wall12);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
NormalEventManager::~NormalEventManager()
{
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		if (m_pEnemyArray[i] != nullptr)
		{
			delete m_pEnemyArray[i];
			m_pEnemyArray[i] = nullptr;
		}
	}

	for (int i = 0; i < m_pWallColliderArray.size(); i++)
	{
		if (m_pWallColliderArray[i] != nullptr)
		{
			ColliderManager::RemoveColliderInfo(m_pWallColliderArray[i]);
			delete m_pWallColliderArray[i];
			m_pWallColliderArray[i] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void NormalEventManager::Init()
{
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void NormalEventManager::Update()
{
	// �G���J�E���g�������̃t���O�ƓG�̏��
	bool EncountFlag = false;
	WalkAroundEnemy* enemy = nullptr;

	// �L�����N�^�̍X�V����
	m_pPlayer->Update();
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		m_pEnemyArray[i]->Update();
		EncountFlag = m_pEnemyArray[i]->GetIsCollisionPlayerFlag();
		if (EncountFlag)
		{
			// �v���C���[�Ɠ������Ă���G�̏�����
			enemy = m_pEnemyArray[i];
			break;
		}
	}

	if (EncountFlag)
	{
		// �G���J�E���g�����G�̏���n���ăo�g���Ǘ��N���X������������.
		m_func(true, enemy);

		// remove�͓���̗v�f�ȊO��L���̈�Ɉړ�������
		auto newend = std::remove(m_pEnemyArray.begin(), m_pEnemyArray.end(), enemy);

		// �ړ������邾���ō폜�͂��Ȃ�����
		// �����̈���폜����ɂ�erase�ƕ��p���Ďg�p����
		m_pEnemyArray.erase(newend, m_pEnemyArray.end());

		// ���������G������
		if (enemy != nullptr)
		{
			delete enemy;
			enemy = nullptr;
		}
	}

	if (Input::IsPress(ENTER))
	{
		if (m_fadeFlag)
		{
			FadeOutInit();
			m_fadeFlag = false;
		}
		else
		{
			FadeInInit();
			m_fadeFlag = true;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void NormalEventManager::Draw()
{
	Field::DrawCall();
	ColliderManager::ColliderVisuale();
	m_pPlayer->Draw();
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		m_pEnemyArray[i]->Draw();
	}

	// ���A�C�R���̃A���t�@�l����
	if (Input::IsPressed(UP))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(250, 850, 1.0f, 0.0f, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(250, 850, 1.0f, 0.0f, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	if (Input::IsPressed(DOWN))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(250, 1000, 1.0f, CollMath::m_pi, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(250, 1000, 1.0f, CollMath::m_pi, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	if (Input::IsPressed(RIGHT))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(400, 1000, 1.0f, CollMath::m_pi / 2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(400, 1000, 1.0f, CollMath::m_pi / 2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	if (Input::IsPressed(LEFT))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(100, 1000, 1.0f, CollMath::m_pi / -2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(100, 1000, 1.0f, CollMath::m_pi / -2, AssetManager::UseImage(AssetManager::Button_Arrow), TRUE);
	}
	// �A���t�@�l�̏�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
