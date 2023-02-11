#include "BattleEscape.h"
#include "Input.h"
#include "PlayScene.h"

BattleEscape::BattleEscape(class PlayScene* _playScene)
{
    m_pPlaySceneStorage = _playScene;
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
        m_pPlaySceneStorage->SetBattleFlag(false);
        m_pPlaySceneStorage->SetNomalState(NormalState::Round1);
    }

    return TAG_BattleState::None;
}

void BattleEscape::Draw()
{
    printfDx("ƒoƒgƒ‹‚©‚ç“¦‚°‚éˆ—");
    DrawFormatString(650, 800, GetColor(255, 255, 255), "í“¬‚©‚ç“¦‚°‚½");
}
