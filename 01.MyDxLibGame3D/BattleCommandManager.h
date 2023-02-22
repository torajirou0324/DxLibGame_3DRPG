//-----------------------------------------------------------------------------
// @brief  �o�g���̃R�}���h�I���Ǘ��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class BattleCommandManager
{
public:
    ~BattleCommandManager() // �f�X�g���N�^
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            delete m_pCommandArray[i];
            m_pCommandArray[i] = nullptr;
        }
        m_pCommandArray.clear();
    }

    void Init()                 // ����������
    {
        index = m_pCommandArray.size() - 1;
    }

    TAG_CommandState Update()   // �X�V����
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->m_display = false;
        }

        if (Input::IsPress(UP))     // ��A���[�L�[�������ꂽ�Ƃ�
        {
            index++;
            if (index >= m_pCommandArray.size())
            {
                index = m_pCommandArray.size() - 1;
            }
        }
        if (Input::IsPress(DOWN))   // ���A���[�L�[�������ꂽ�Ƃ�
        {
            index--;
            if (index < 0)
            {
                index = 0;
            }
        }

        return m_pCommandArray[index]->Execute();
    }

    void Draw()     // �`�揈��
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->Draw(975 - (80 * i));
        }
    }

    void SetCommand(Command* _command)  // �������ꂽ�R�}���h���i�[����
    {
        m_pCommandArray.push_back(_command);
    }
private:
    std::vector<Command*> m_pCommandArray;  // �R�}���h�i�[�z��
    int index;                              // �R�}���h�ԍ�
};