//-----------------------------------------------------------------------------
// @brief  バトルイベントの攻撃目標表示コマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class TargetCommand : public Command
{
public:
    // コンストラクタ
    TargetCommand(std::function<void(Enemy*)> _func, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : SetAttackObj(_func)
        , m_obj(nullptr)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
    {
    }
    // デストラクタ
    ~TargetCommand() override {}

    // 初期化処理
    void Init(Enemy* _enemy) override
    {
        m_obj = _enemy;
    }

    // 更新処理
    TAG_CommandState Execute() override;

    // 描画処理
    void Draw(int posY) const override;
private:
    std::function<void(Enemy*)> SetAttackObj;
    Enemy* m_obj;
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};