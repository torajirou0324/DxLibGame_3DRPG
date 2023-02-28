#include "BattleEscape.h"

#include "Input.h"
#include "BattleEventManager.h"

BattleEscape::BattleEscape(class BattleEventManager* _manager)
{
    m_pBattleManager = _manager;
}

BattleEscape::~BattleEscape()
{
}

void BattleEscape::Init()
{
}

TAG_BattleState BattleEscape::Update()
{
    if (Input::IsPress(ENTER))
    {
        m_pBattleManager->m_func(false);
    }

    return TAG_BattleState::None;
}

void BattleEscape::Draw()
{
    printfDx("ƒoƒgƒ‹‚©‚ç“¦‚°‚éˆ—");
    DrawFormatString(650, 800, GetColor(255, 255, 255), "í“¬‚©‚ç“¦‚°‚½");
    DrawArrowVertical(1240, 950);      // –îˆó‚Ì•\¦
}
