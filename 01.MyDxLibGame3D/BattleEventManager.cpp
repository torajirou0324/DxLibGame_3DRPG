//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�Ǘ��N���X.
//-----------------------------------------------------------------------------
#include "BattleEventManager.h"
#include "BattleStart.h"
#include "BattleCommand.h"
#include "BattleComparison.h"
#include "BattleMoveMentStart.h"
#include "BattleMoveMentEnd.h"
#include "BattleEscape.h"
#include "BattleVictory.h"
#include "BattleDefeat.h"
#include "BattleContinue.h"
#include "PlayScene.h"
#include "Field.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleEventManager::BattleEventManager(Player* _player, std::vector<Enemy*> _enemyArray, std::function<void(bool)> _func)
	: m_pPlayer(_player)
	, m_pEnemyArray(_enemyArray)
	, m_pAttackNowCharacter(nullptr)
	, m_func(_func)
{
	// �o�g���X�e�[�g�̏�����
	m_battleState = TAG_BattleState::Start;
	m_pBattleStateArray.push_back(new BattleStart(this));
	m_pBattleStateArray.push_back(new BattleCommand(this));
	m_pBattleStateArray.push_back(new BattleComparison(this));
	m_pBattleStateArray.push_back(new BattleMoveMentStart(this));
	m_pBattleStateArray.push_back(new BattleMoveMentEnd(this));
	m_pBattleStateArray.push_back(new BattleEscape(this));
	m_pBattleStateArray.push_back(new BattleVictory(this));
	m_pBattleStateArray.push_back(new BattleDefeat(this));
	m_pBattleStateArray.push_back(new BattleContinue(this));
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleEventManager::~BattleEventManager()
{
	for (const auto it : m_pBattleStateArray)
	{
		delete it;
	}
	m_pBattleStateArray.clear();
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleEventManager::Init(class Player* _player, std::vector<class Enemy*> _enemyArray)
{
	// �o�g���X�e�[�g���X�^�[�g�ɏ�����
	m_battleState = TAG_BattleState::Start;

	// �v���C���[�ƓG��������
	m_pPlayer = _player;
	m_pEnemyArray = _enemyArray;
	// �L�����N�^�[�z������������Z�b�g
	m_pCharacterArray.clear();
	m_pCharacterArray.push_back(m_pPlayer);
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		m_pCharacterArray.push_back(m_pEnemyArray[i]);
	}
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void BattleEventManager::Update()
{
	m_pPlayer->Animation();
	for (int i = 0; i < m_pEnemyArray.size(); i++)
	{
		m_pEnemyArray[i]->Update();
	}

	auto tag = m_pBattleStateArray[m_battleState]->Update();

	if (tag != TAG_BattleState::None)
	{
		m_battleState = tag;
		m_pBattleStateArray[tag]->Init();
	}
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleEventManager::Draw()
{
	Field::BattleDrawCall();

	auto white = GetColor(255, 255, 255);	// ��
	auto black = GetColor(0, 0, 0);			// ��

	DrawGraph(600, 750, AssetManager::UseImage(AssetManager::BlackWindow), TRUE);					// �����o���E�B���h�E�̕\��

	SetFontSize(30);
	// �v���C���[�̃X�e�[�^�X�\��+���g
	{
		DrawGraph(0, 750, AssetManager::UseImage(AssetManager::StatusWindow), TRUE);
		auto& playerStatus = m_pPlayer->GetAllStatus();
		DrawFormatString(50, 786, GetColor(255, 255, 255), "Lv.%d�@�@�@�L�c�L�@�C�`�J", playerStatus.LV);

		float berdif = static_cast<float>(playerStatus.EXP) / m_pPlayer->GetEXPMAX();
		auto ber = 270 * berdif;
		DrawBox(50, 840, 50 + ber, 860, GetColor(0, 255, 255), TRUE);
		DrawBox(48, 838, 322, 862, GetColor(255, 255, 255), FALSE);

		berdif = static_cast<float>(playerStatus.HP) / m_pPlayer->GetHPMAX();
		ber = 350 * berdif;
		DrawBox(50, 870, 50 + ber, 910, GetColor(0, 255, 0), TRUE);
		DrawBox(48, 868, 402, 912, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 880, GetColor(255, 255, 255), "%d/%d", playerStatus.HP, m_pPlayer->GetHPMAX());

		berdif = static_cast<float>(playerStatus.MP) / m_pPlayer->GetMPMAX();
		ber = 350 * berdif;
		DrawBox(50, 920, 50 + ber, 960, GetColor(0, 100, 200), TRUE);
		DrawBox(48, 918, 402, 962, GetColor(255, 255, 255), FALSE);
		DrawFormatString(300, 927, GetColor(255, 255, 255), "%d/%d", playerStatus.MP, m_pPlayer->GetMPMAX());
	}

	// �G�l�~�[�̃X�e�[�^�X�\��+���g
	{
		for (int i = 0; i < m_pEnemyArray.size(); i++)
		{
			int addNum = i + 1;
			DrawGraph(1920 - (520 * addNum), 0, AssetManager::UseImage(AssetManager::StatusWindow), TRUE);
			auto& enemyStatus = m_pEnemyArray[i]->GetAllStatus();
			float HPberdif = static_cast<float>(enemyStatus.HP) / m_pEnemyArray[i]->GetHPMAX();
			auto HPber = 350 * HPberdif;

			DrawFormatString(1920 - (520 * addNum) + 50, 36, GetColor(255, 255, 255), "Lv.%d�@�@%s", enemyStatus.LV, m_pEnemyArray[i]->GetName().c_str());
			DrawBox(1920 - (520 * addNum) + 50, 140, (1920 - (520 * addNum) + 50) + HPber, 180, GetColor(0, 255, 0), TRUE);
			DrawBox(1918 - (520 * addNum) + 50, 138, (1920 - (520 * addNum) + 50) + 352, 182, GetColor(255, 255, 255), FALSE);
			DrawFormatString(1920 - (520 * addNum) + 300, 150, GetColor(255, 255, 255), "%d/%d", enemyStatus.HP, m_pEnemyArray[i]->GetHPMAX());
		}
	}

	m_pBattleStateArray[m_battleState]->Draw();
}
