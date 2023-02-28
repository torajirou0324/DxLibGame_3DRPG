#include "BattleEscape.h"

#include "Input.h"
#include "BattleEventManager.h"

BattleEscape::BattleEscape(class BattleEventManager* _manager)
{
    m_pBattleManager = _manager;
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
        m_pBattleManager->m_func(false);
    }

    return TAG_BattleState::None;
}

void BattleEscape::Draw()
{
    printfDx("�o�g�����瓦���鏈��");
    DrawFormatString(650, 800, GetColor(255, 255, 255), "�퓬���瓦����");
    DrawArrowVertical(1240, 950);      // ���̕\��
}
