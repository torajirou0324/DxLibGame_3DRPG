#include "BattleVictory.h"
#include "Input.h"
#include "PlayScene.h"

BattleVictory::BattleVictory(class PlayScene* _playScene)
{
    m_pPlaySceneStorage = _playScene;
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
        m_pPlaySceneStorage->SetBattleFlag(false);
        auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
        for (auto it : CharacterALL)
        {
            it->ActionInit();
        }
        int EventNum = m_pPlaySceneStorage->GetNomalState();
        EventNum++;
        if (EventNum > NormalState::Boss)
        {
            EventNum = NormalState::Boss;
        }
        m_pPlaySceneStorage->SetNomalState(static_cast<NormalState>(EventNum));
    }

    return TAG_BattleState::None;
}

void BattleVictory::Draw()
{
    printfDx("ƒoƒgƒ‹Ÿ—˜ˆ—");
    auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
    for (int i = 1; i < CharacterALL.size(); i++)
    {
        DrawFormatString(650, 740 + (60 * i), GetColor(255, 255, 255), "%s‚ð“|‚µ‚½", CharacterALL[i]->GetName().c_str());
    }
    DrawArrowVertical(1240, 950);      // –îˆó‚Ì•\Ž¦
}
