//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̑f������r�����N���X.
//-----------------------------------------------------------------------------
#include "BattleComparison.h"
#include "PlayScene.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleComparison::BattleComparison(class PlayScene* _playScene)
{
    m_pPlaySceneStorage = _playScene;
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleComparison::~BattleComparison()
{
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleComparison::Init()
{
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleComparison::Update()
{
    auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
    for (int i = 0; i < CharacterALL.size(); i++)
    {
        for (int j = 0; j < CharacterALL.size(); j++)
        {
            if (i == j)
            {

            }
            else
            {
                if (CharacterALL[i]->GetAllStatus().AGL > CharacterALL[j]->GetAllStatus().AGL)
                {
                    if (i < j)
                    {

                    }
                    else
                    {
                        auto tmp = CharacterALL[i];
                        CharacterALL[i] = CharacterALL[j];
                        CharacterALL[j] = tmp;
                    }
                }
            }
        }
    }

    return TAG_BattleState::MoveMentStart;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleComparison::Draw()
{
    printfDx("�f������r����");
}
