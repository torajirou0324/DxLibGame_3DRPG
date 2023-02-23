//-----------------------------------------------------------------------------
// @brief  バトルイベントの攻撃目標表示コマンド選択処理クラス.
//-----------------------------------------------------------------------------
#include "TargetCommand.h"

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_CommandState TargetCommand::Execute()
{
    // 現在選択中のコマンドであるかどうかを返す
    m_display = true;

    // 攻撃目標の情報が入っているときでないとセットできない
    if (Input::IsPress(ENTER) && m_obj != nullptr)
    {
        SetAttackObj(m_obj);
        return m_nextCommandType;
    }
    if (Input::IsPress(BACK))
    {
        return m_backCommandType;
    }
    return TAG_CommandState::TAG_None;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void TargetCommand::Draw(int posY) const
{
    if (m_display)
    {
        DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
        if (m_obj != nullptr)
        {
            DrawFormatString(1480, posY + 10, GetColor(0, 0, 0), "%s", m_obj->GetName().c_str());
        }

        DrawArrowSide(1360, posY + 15);
        return;
    }
    DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
    if (m_obj != nullptr)
    {
        DrawFormatString(1480, posY + 10, GetColor(255, 255, 255), "%s", m_obj->GetName().c_str());
    }
}
