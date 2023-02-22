//-----------------------------------------------------------------------------
// @brief  バトルイベントの純粋なテキスト表示コマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class SimpleCommand : public Command
{
public:
    SimpleCommand(std::string _str, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : m_text(_str)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
    {
    }
    ~SimpleCommand() override {}

    TAG_CommandState Execute() override
    {
        m_display = true;
        if (Input::IsPress(ENTER))
        {
            return m_nextCommandType;
        }
        if (Input::IsPress(BACK))
        {
            return m_backCommandType;
        }
        
        return TAG_CommandState::TAG_None;
    }

    void Draw(int posY) const override
    {
        if (m_display)
        {
            DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
            DrawFormatString(1480, posY + 10, GetColor(0, 0, 0), "%s", m_text.c_str());
            return;
        }
        DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
        DrawFormatString(1480, posY + 10, GetColor(255, 255, 255), "%s", m_text.c_str());
    }
private:
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};