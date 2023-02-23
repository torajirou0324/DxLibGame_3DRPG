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
BattleEventManager::BattleEventManager(class PlayScene* scene)
{
	// �o�g���X�e�[�g�̏�����
	m_battleState = TAG_BattleState::Start;
	m_pBattleStateArray.push_back(new BattleStart(scene));
	m_pBattleStateArray.push_back(new BattleCommand(scene));
	m_pBattleStateArray.push_back(new BattleComparison(scene));
	m_pBattleStateArray.push_back(new BattleMoveMentStart(scene));
	m_pBattleStateArray.push_back(new BattleMoveMentEnd(scene));
	m_pBattleStateArray.push_back(new BattleEscape(scene));
	m_pBattleStateArray.push_back(new BattleVictory(scene));
	m_pBattleStateArray.push_back(new BattleDefeat(scene));
	m_pBattleStateArray.push_back(new BattleContinue(scene));
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

	// �o�g���R�}���h�̋Z�ƍU���Ώۂ̓G��������
	m_pBattleStateArray[TAG_BattleState::CommandProcess]->Init(_player, _enemyArray);
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void BattleEventManager::Update()
{
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
	m_pBattleStateArray[m_battleState]->Draw();
}
