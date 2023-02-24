//-----------------------------------------------------------------------------
// @brief  �o�g���̃R�}���h�I���Ǘ��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class BattleCommandManager
{
public:
    // �f�X�g���N�^
    ~BattleCommandManager()
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            delete m_pCommandArray[i];
            m_pCommandArray[i] = nullptr;
        }
        m_pCommandArray.clear();
    }

    // ���ʂ̏���������
    void Init()
    {
        index = m_pCommandArray.size() - 1;
    }

    // �Z�݂̂̏���������
    void Init(const SKILL* _skillStorage)
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            SKILL skill = _skillStorage[i];
            m_pCommandArray[i]->Init(skill);
        }
    }

    // �U���ڕW�݂̂̏���������
    void Init(std::vector<class Enemy*> _enemyArray)
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->Init(nullptr);
        }

        for (int i = 0; i < _enemyArray.size(); i++)
        {
            Enemy* enemy = _enemyArray[i];
            m_pCommandArray[i]->Init(enemy);
        }
    }

    // �X�V����
    TAG_CommandState Update()
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

    // �`�揈��
    void Draw()
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->Draw(975 - (80 * i));
        }
    }

    // �������ꂽ�R�}���h���i�[����
    void SetCommand(Command* _command)
    {
        m_pCommandArray.push_back(_command);
    }
private:
    std::vector<Command*> m_pCommandArray;  // �R�}���h�i�[�z��
    int index;                              // �R�}���h�ԍ�
};