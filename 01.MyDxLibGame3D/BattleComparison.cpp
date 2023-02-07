#include "BattleComparison.h"
#include "Input.h"

BattleComparison::BattleComparison()
{
}

BattleComparison::~BattleComparison()
{
}

void BattleComparison::Init()
{
}

TAG_BattleState BattleComparison::Update()
{
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::MoveMentStart;
    }

    return TAG_BattleState::Comparison;
}

void BattleComparison::Draw()
{
    printfDx("ëfëÅÇ≥î‰ärèàóù");
}
