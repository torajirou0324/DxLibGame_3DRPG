//-----------------------------------------------------------------------------
// @brief  インプットクラス（キー入力）.
//-----------------------------------------------------------------------------
#include "Input.h"
#include <DxLib.h>

Input* Input::input = nullptr;

Input::Input()
{
    key k;
    k.pressCount = 0;
    for (int i = 0; i < END; i++)
    {
        keynum.push_back(k);
    }
}

Input::~Input()
{
    keynum.clear();
}

void Input::CreateInstance()
{
    if (input == nullptr)
    {
        input = new Input;
    }
}

void Input::DeleteInstance()
{
    if (input != nullptr)
    {
        delete input;
        input = nullptr;
    }
}

void Input::Update()
{
    //for (int i = 0; i < END; i++)
    //{
    //    if (GetAsyncKeyState(input->keynum[i].pressCount & 0x8000))
    //    {
    //        input->keynum[i].pressCount = max(++input->keynum[i].pressCount, 1);
    //    }
    //    else
    //    {
    //        input->keynum[i].pressCount = min(--input->keynum[i].pressCount, 0);
    //    }
    //}

    // ESCAPE
    {
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            input->keynum[ESCAPE].pressCount = max(++input->keynum[ESCAPE].pressCount, 1);
        }
        else
        {
            input->keynum[ESCAPE].pressCount = min(--input->keynum[ESCAPE].pressCount, 0);
        }
    }
    // UP
    {
        if (CheckHitKey(KEY_INPUT_UP))
        {
            input->keynum[UP].pressCount = max(++input->keynum[UP].pressCount, 1);
        }
        else
        {
            input->keynum[UP].pressCount = min(--input->keynum[UP].pressCount, 0);
        }
    }
    // DOWN
    {
        if (CheckHitKey(KEY_INPUT_DOWN))
        {
            input->keynum[DOWN].pressCount = max(++input->keynum[DOWN].pressCount, 1);
        }
        else
        {
            input->keynum[DOWN].pressCount = min(--input->keynum[DOWN].pressCount, 0);
        }
    }
    // LEFT
    {
        if (CheckHitKey(KEY_INPUT_LEFT))
        {
            input->keynum[LEFT].pressCount = max(++input->keynum[LEFT].pressCount, 1);
        }
        else
        {
            input->keynum[LEFT].pressCount = min(--input->keynum[LEFT].pressCount, 0);
        }
    }
    // RIGHT
    {
        if (CheckHitKey(KEY_INPUT_RIGHT))
        {
            input->keynum[RIGHT].pressCount = max(++input->keynum[RIGHT].pressCount, 1);
        }
        else
        {
            input->keynum[RIGHT].pressCount = min(--input->keynum[RIGHT].pressCount, 0);
        }
    }
    // ENTER
    {
        if (CheckHitKey(KEY_INPUT_RETURN))
        {
            input->keynum[ENTER].pressCount = max(++input->keynum[ENTER].pressCount, 1);
        }
        else
        {
            input->keynum[ENTER].pressCount = min(--input->keynum[ENTER].pressCount, 0);
        }
    }
    // BACK
    {
        if (CheckHitKey(KEY_INPUT_BACK))
        {
            input->keynum[BACK].pressCount = max(++input->keynum[BACK].pressCount, 1);
        }
        else
        {
            input->keynum[BACK].pressCount = min(--input->keynum[BACK].pressCount, 0);
        }
    }
}
