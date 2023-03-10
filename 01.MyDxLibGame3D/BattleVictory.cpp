#include "BattleVictory.h"

#include "Input.h"
#include "BattleEventManager.h"

BattleVictory::BattleVictory(class BattleEventManager* _manager)
{
    m_pBattleManager = _manager;
}

BattleVictory::~BattleVictory()
{
}

void BattleVictory::Init()
{
}

TAG_BattleState BattleVictory::Update()
{
    if (Input::IsPress(ENTER))
    {
        m_pBattleManager->m_func(false);
        auto& CharacterALL = m_pBattleManager->m_pCharacterArray;
        for (auto it : CharacterALL)
        {
            it->ActionInit();
        }
    }

    return TAG_BattleState::None;
}

void BattleVictory::Draw()
{
    printfDx("バトル勝利処理");
    auto& EnemyALL = m_pBattleManager->m_pEnemyArray;
    for (int i = 0; i < EnemyALL.size(); i++)
    {
        DrawFormatString(650, 740 + (60 * i), GetColor(255, 255, 255), "%sを倒した", EnemyALL[i]->GetName().c_str());
    }
    DrawArrowVertical(1240, 950);      // 矢印の表示
}
