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
        return TAG_BattleState::Defeat;
    }

    return TAG_BattleState::None;
}

void BattleVictory::Draw()
{
    printfDx("ƒoƒgƒ‹Ÿ—˜ˆ—");
}
