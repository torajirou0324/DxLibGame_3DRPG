//-----------------------------------------------------------------------------
// @brief  バトルイベントの技表示コマンド選択処理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class SkillCommand : public Command
{
public:
    // コンストラクタ
    SkillCommand(std::function<void(SKILL)> _func, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : SetPlayerSkill(_func)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
        , m_skill()
    {
    }
    // デストラクタ
    ~SkillCommand() override {}

    // 初期化処理
    void Init(SKILL _skill) override
    {
        m_skill = _skill;
    }

    // 更新処理
    TAG_CommandState Execute() override;

    // 描画処理
    void Draw(int posY) const override;
private:
    std::function<void(SKILL)> SetPlayerSkill;
    SKILL m_skill;
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};