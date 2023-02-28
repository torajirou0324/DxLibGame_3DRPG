#include "BattleDefeat.h"

#include "Input.h"
#include "BattleEventManager.h"

BattleDefeat::BattleDefeat(class BattleEventManager* _manager)
{
    m_pBattleManager = _manager;
}

BattleDefeat::~BattleDefeat()
{
}

void BattleDefeat::Init()
{
}

TAG_BattleState BattleDefeat::Update()
{
    if (Input::IsPress(ENTER))
    {
        m_pBattleManager->m_func(false);
        auto& CharacterALL = m_pBattleManager->m_pCharacterArray;
        for (auto it : CharacterALL)
        {
            it->ActionInit();
        }
    }

    return TAG_BattleState::None;
}

void BattleDefeat::Draw()
{
    printfDx("ƒoƒgƒ‹”s–kˆ—");
    auto player = m_pBattleManager->m_pPlayer;
    DrawFormatString(650, 800, GetColor(255, 255, 255), "%s‚Í“|‚ê‚½", player->GetName().c_str());
    DrawArrowVertical(1240, 950);      // –îˆó‚Ì•\Ž¦
}
