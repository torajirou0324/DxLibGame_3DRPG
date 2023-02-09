#include "BattleDefeat.h"
#include "Input.h"
#include "PlayScene.h"

BattleDefeat::BattleDefeat()
{
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
        m_pPlayScene->SetBattleFlag(false);
        for (auto it : m_pCharacter)
        {
            it->ActionInit();
        }
    }

    return TAG_BattleState::None;
}

void BattleDefeat::Draw()
{
    printfDx("ƒoƒgƒ‹”s–kˆ—");
}
