#include "BattleMoveMentStart.h"
#include "Input.h"

BattleMoveMentStart::BattleMoveMentStart()
{
}

BattleMoveMentStart::~BattleMoveMentStart()
{
}

void BattleMoveMentStart::Init()
{
}

TAG_BattleState BattleMoveMentStart::Update()
{
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::MoveMentEnd;
    }

    return TAG_BattleState::MoveMentStart;
}

void BattleMoveMentStart::Draw()
{
    printfDx("‘SƒLƒƒƒ‰s“®ˆ—");
}
