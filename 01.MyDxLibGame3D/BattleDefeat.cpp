#include "BattleDefeat.h"
#include "Input.h"
#include "PlayScene.h"

BattleDefeat::BattleDefeat(class PlayScene* _playScene)
{
    m_pPlaySceneStorage = _playScene;
}

BattleDefeat::~BattleDefeat()
{
}

void BattleDefeat::Init()
{
}

TAG_BattleState BattleDefeat::Update()
{
    if (Input::IsPress(ENTER))
    {
        m_pPlaySceneStorage->SetBattleFlag(false);
        auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
        for (auto it : CharacterALL)
        {
            it->ActionInit();
        }
    }

    return TAG_BattleState::None;
}

void BattleDefeat::Draw()
{
    printfDx("�o�g���s�k����");
    auto player = m_pPlaySceneStorage->GetPlayerAddress();
    DrawFormatString(650, 800, GetColor(255, 255, 255), "%s�͓|�ꂽ", player->GetName().c_str());
    DrawArrowVertical(1240, 950);      // ���̕\��
}
