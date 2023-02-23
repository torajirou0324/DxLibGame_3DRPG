//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̋Z�\���R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class SkillCommand : public Command
{
public:
    // �R���X�g���N�^
    SkillCommand(std::function<void(SKILL)> _func, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : SetPlayerSkill(_func)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
        , m_skill()
    {
    }
    // �f�X�g���N�^
    ~SkillCommand() override {}

    // ����������
    void Init(SKILL _skill) override
    {
        m_skill = _skill;
    }

    // �X�V����
    TAG_CommandState Execute() override;

    // �`�揈��
    void Draw(int posY) const override;
private:
    std::function<void(SKILL)> SetPlayerSkill;
    SKILL m_skill;
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};