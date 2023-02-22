#pragma once
#include "Command.h"

class SkillCommand : public Command
{
public:
    SkillCommand(std::function<void(SKILL)> _func, SKILL _skill, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : SetPlayerSkill(_func)
        , m_skill(_skill)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
    {
    }
    ~SkillCommand() override {}

    TAG_CommandState Execute() override
    {
        m_display = true;

        if (Input::IsPress(ENTER))
        {
            SetPlayerSkill(m_skill);
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
            DrawFormatString(1480, posY + 10, GetColor(0, 0, 0), "%s", m_skill.SkillName.c_str());
            return;
        }
        DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
        DrawFormatString(1480, posY + 10, GetColor(255, 255, 255), "%s", m_skill.SkillName.c_str());
    }
private:
    std::function<void(SKILL)> SetPlayerSkill;
    SKILL m_skill;
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};