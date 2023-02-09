#include "BattleVictory.h"
#include "Input.h"
#include "PlayScene.h"

BattleVictory::BattleVictory()
{
}

BattleVictory::~BattleVictory()
{
}

void BattleVictory::Init()
{
}

TAG_BattleState BattleVictory::Update()
{
    if (Input::IsPress(ENTER))
    {
        m_pPlayScene->SetBattleFlag(false);
        for (auto it : m_pCharacter)
        {
            it->ActionInit();
        }
        int EventNum = m_pPlayScene->GetNomalState();
        EventNum++;
        if (EventNum > NormalState::Boss)
        {
            EventNum = NormalState::Boss;
        }
        m_pPlayScene->SetNomalState(static_cast<NormalState>(EventNum));
    }

    return TAG_BattleState::None;
}

void BattleVictory::Draw()
{
    printfDx("�o�g����������");
    for (int i = 1; i < m_pCharacter.size(); i++)
    {
        DrawFormatString(650, 740 + (60 * i), GetColor(255, 255, 255), "%s��|����", m_pCharacter[i]->GetName().c_str());
    }

}
