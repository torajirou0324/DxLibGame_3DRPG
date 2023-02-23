//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̏����ȃe�L�X�g�\���R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class SimpleCommand : public Command
{
public:
    // �R���X�g���N�^
    SimpleCommand(std::string _str, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : m_text(_str)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
    {
    }
    // �f�X�g���N�^
    ~SimpleCommand() override {}

    // �X�V����
    TAG_CommandState Execute() override;
    // �`�揈��
    void Draw(int posY) const override;
private:
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};