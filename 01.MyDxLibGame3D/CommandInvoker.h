#pragma once
#include <vector>
#include "SimpleCommand.h"

class CommandInvoker
{
public:
    explicit CommandInvoker(std::string _str)
        : m_commandName(_str)
    {
    }
    ~CommandInvoker()
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            if (m_pCommandArray[i] != nullptr)
            {
                delete m_pCommandArray[i];
                m_pCommandArray[i] = nullptr;
            }
        }
        m_pCommandArray.clear();
    }

    void SetOnCommand(Command* _command)
    {
        m_pCommandArray.push_back(_command);
    }

    void Update()
    {
        if (m_dicide)
        {
            m_pCommandArray[m_commandNum]->m_display = false;
            m_pCommandArray[m_commandNum]->Execute();
        }


        if (Input::IsPress(ENTER))
        {
            m_dicide = true;
        }
        if (Input::IsPress(BACK))
        {
            m_dicide = false;
        }
        if (Input::IsPress(UP))
        {
            m_commandNum++;
        }
        if (Input::IsPress(DOWN))
        {
            m_commandNum--;
        }
        if (m_commandNum < 0) { m_commandNum = 0; }
        if (m_commandNum > 3) { m_commandNum = 3; }

        m_display = true;
    }

    void Draw(int posY)
    {
        if (m_dicide)
        {
            for (int i = 0; i < m_pCommandArray.size(); i++)
            {
                m_pCommandArray[i]->Draw(975 - (80 * i));
            }
            return;
        }
        else
        {
            if (m_display)
            {
                DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
                DrawFormatString(1480, posY + 10, GetColor(0, 0, 0), "%s", m_commandName.c_str());
                return;
            }
            DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
            DrawFormatString(1480, posY + 10, GetColor(255, 255, 255), "%s", m_commandName.c_str());
        }
    }

    const bool& GetDicideFlag() { return m_dicide; }

    bool m_display = false;
private:
    std::vector<Command*> m_pCommandArray;
    std::string m_commandName;
    bool m_dicide = false;
    int m_commandNum = 0;
};