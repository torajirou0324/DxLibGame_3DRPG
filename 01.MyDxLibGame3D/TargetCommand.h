//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̍U���ڕW�\���R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class TargetCommand : public Command
{
public:
    // �R���X�g���N�^
    TargetCommand(std::function<void(Enemy*)> _func, TAG_CommandState _nextcommand, TAG_CommandState _backcommand)
        : SetAttackObj(_func)
        , m_obj(nullptr)
        , m_nextCommandType(_nextcommand)
        , m_backCommandType(_backcommand)
    {
    }
    // �f�X�g���N�^
    ~TargetCommand() override {}

    // ����������
    void Init(Enemy* _enemy) override
    {
        m_obj = _enemy;
    }

    // �X�V����
    TAG_CommandState Execute() override;

    // �`�揈��
    void Draw(int posY) const override;
private:
    std::function<void(Enemy*)> SetAttackObj;
    Enemy* m_obj;
    std::string m_text;
    TAG_CommandState m_nextCommandType;
    TAG_CommandState m_backCommandType;
};