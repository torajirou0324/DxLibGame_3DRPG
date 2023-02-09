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
    }

    void SetOnCommand(Command* _command)
    {
        m_pCommandArray.push_back(_command);
    }

    void Update()
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->Execute();
        }
        m_dicide = false;
    }

    void Draw(int posY)
    {
        if (m_dicide)
        {
            for (int i = 0; i < m_pCommandArray.size(); i++)
            {
                m_pCommandArray[i]->Draw(975);
            }
            return;
        }
        else
        {
            DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
            DrawFormatString(1480, posY + 10, GetColor(0, 0, 0), "%s", m_commandName.c_str());
            return;
        }
        DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
        DrawFormatString(1480, posY + 10, GetColor(255, 255, 255), "%s", m_commandName.c_str());
    }

    bool m_dicide = false;
    std::string m_commandName;
private:
    std::vector<Command*> m_pCommandArray;
};