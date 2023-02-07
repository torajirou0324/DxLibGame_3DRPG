#include "BattleCommand.h"
#include "Input.h"

BattleCommand::BattleCommand()
{
}

BattleCommand::~BattleCommand()
{
}

void BattleCommand::Init()
{
}

TAG_BattleState BattleCommand::Update()
{
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::Comparison;
    }

    return TAG_BattleState::Command;
}

void BattleCommand::Draw()
{
    printfDx("コマンド選択処理");
}
