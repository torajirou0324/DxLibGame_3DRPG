//-----------------------------------------------------------------------------
// @brief  インプットクラス（キー入力）.
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
    // コピー禁止
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    Input();
    ~Input();

    static void CreateInstance();
    static void DeleteInstance();

    static void Update();

    // 押した瞬間
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
    
    // 押している時
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

    // 離した瞬間
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

    // 離している時
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