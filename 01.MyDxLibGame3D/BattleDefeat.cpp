#include "BattleDefeat.h"
#include "Input.h"
#include "PlayScene.h"

BattleDefeat::BattleDefeat()
{
}

BattleDefeat::~BattleDefeat()
{
}

void BattleDefeat::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
}

TAG_BattleState BattleDefeat::Update()
{
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::Continue;
    }

    return TAG_BattleState::None;
}

void BattleDefeat::Draw()
{
    printfDx("�o�g���s�k����");
}
