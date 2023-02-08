#include "BattleVictory.h"
#include "Input.h"
#include "PlayScene.h"

BattleVictory::BattleVictory()
{
}

BattleVictory::~BattleVictory()
{
}

void BattleVictory::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
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
    printfDx("ƒoƒgƒ‹Ÿ—˜ˆ—");
    for (int i = 1; i < m_pCharacter.size(); i++)
    {
        DrawFormatString(650, 740 + (60 * i), GetColor(255, 255, 255), "%s‚ğ“|‚µ‚½", m_pCharacter[i]->GetName().c_str());
    }

}
