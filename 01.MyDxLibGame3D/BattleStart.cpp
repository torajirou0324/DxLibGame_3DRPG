#include "BattleStart.h"
#include "Input.h"

BattleStart::BattleStart()
{
}

BattleStart::~BattleStart()
{
}

void BattleStart::Init()
{
}

TAG_BattleState BattleStart::Update()
{
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::Command;
    }

    return TAG_BattleState::Start;
}

void BattleStart::Draw()
{
    printfDx("バトル開始処理");
}
