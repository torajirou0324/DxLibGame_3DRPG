#pragma once
#include "Command.h"

class SimpleCommand : public Command
{
public:
    explicit SimpleCommand(std::function<void(MoveCommand)> _function, std::string _str, MoveCommand _moveCommand)
        : m_pFunction(_function)
        , m_commandName(_str)
        , m_moveCommand(_moveCommand)
    {
    }

    void Execute() const override {
        if (Input::IsPress(ENTER))
        {
            this->m_pFunction(m_moveCommand);
        }
    }

    void Draw(int posY) const override
    {

    }
private:
    std::function<void(MoveCommand)> m_pFunction;
    std::string m_commandName;
    MoveCommand m_moveCommand;
};