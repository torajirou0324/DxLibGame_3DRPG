#pragma once
#include "Command.h"

class SimpleCommand : public Command
{
public:
    SimpleCommand(Player* _player, SKILL _skill)
        : m_orignPlayer(_player)
        , m_skill(_skill)
    {
    }
    ~SimpleCommand() override {}

    void Execute() override 
    {
        if (Input::IsPress(ENTER))
        {
            m_orignPlayer->SetUseSkill(m_skill);
        }
        m_display = true;
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
    Player* m_orignPlayer;
    SKILL m_skill;

};