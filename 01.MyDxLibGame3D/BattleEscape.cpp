#include "BattleEscape.h"
#include "Input.h"
#include "PlayScene.h"

BattleEscape::BattleEscape()
{
}

BattleEscape::~BattleEscape()
{
}

void BattleEscape::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
}

TAG_BattleState BattleEscape::Update()
{
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::Victory;
    }

    return TAG_BattleState::None;
}

void BattleEscape::Draw()
{
    printfDx("ƒoƒgƒ‹‚©‚ç“¦‚°‚éˆ—");
    DrawFormatString(650, 800, GetColor(255, 255, 255), "í“¬‚©‚ç“¦‚°‚½");
}
