//-----------------------------------------------------------------------------
// @brief  �C���v�b�g�N���X�i�L�[���́j.
//-----------------------------------------------------------------------------
#pragma once
#include <vector>

enum TYPE
{
    ESCAPE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    BACK,
    END
};

class Input
{
    static Input* input;
    struct key
    {
        int pressCount;
    };
    std::vector<key> keynum;

public:
    // �R�s�[�֎~
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    Input();
    ~Input();

    static void CreateInstance();
    static void DeleteInstance();

    static void Update();

    // �������u��
    static bool IsPress(TYPE t)
    {
        if (input->keynum[t].pressCount == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    // �����Ă��鎞
    static bool IsPressed(TYPE t)
    {
        if (input->keynum[t].pressCount > 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // �������u��
    static bool NoPress(TYPE t)
    {
        if (input->keynum[t].pressCount == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // �����Ă��鎞
    static bool NoPressed(TYPE t)
    {
        if (input->keynum[t].pressCount < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};