//-----------------------------------------------------------------------------
// @brief  バトルイベントの純粋なテキスト表示コマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class SimpleCommand : public Command
{
public:
    // コンストラクタ
    SimpleCommand(std::string _str, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : m_text(_str)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
    {
    }
    // デストラクタ
    ~SimpleCommand() override {}

    // 更新処理
    TAG_CommandState Execute() override;
    // 描画処理
    void Draw(int posY) const override;
private:
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};