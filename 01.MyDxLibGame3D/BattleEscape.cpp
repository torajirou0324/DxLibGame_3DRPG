#include "BattleEscape.h"
#include "Input.h"
#include "PlayScene.h"

BattleEscape::BattleEscape()
{
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
        m_pPlayScene->SetBattleFlag(false);
        m_pPlayScene->SetNomalState(NormalState::Round1);
    }

    return TAG_BattleState::None;
}

void BattleEscape::Draw()
{
    printfDx("�o�g�����瓦���鏈��");
    DrawFormatString(650, 800, GetColor(255, 255, 255), "�퓬���瓦����");
}
