#include "BattleMoveMentEnd.h"
#include "Input.h"

BattleMoveMentEnd::BattleMoveMentEnd()
{
}

BattleMoveMentEnd::~BattleMoveMentEnd()
{
}

void BattleMoveMentEnd::Init()
{
}

TAG_BattleState BattleMoveMentEnd::Update()
{
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::Escape;
    }

    return TAG_BattleState::MoveMentEnd;
}

void BattleMoveMentEnd::Draw()
{
    printfDx("全キャラ行動完了待機処理");
}
