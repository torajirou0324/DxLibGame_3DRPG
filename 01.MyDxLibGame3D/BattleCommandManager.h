//-----------------------------------------------------------------------------
// @brief  バトルのコマンド選択管理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class BattleCommandManager
{
public:
    ~BattleCommandManager() // デストラクタ
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            delete m_pCommandArray[i];
            m_pCommandArray[i] = nullptr;
        }
        m_pCommandArray.clear();
    }

    void Init()                 // 初期化処理
    {
        index = m_pCommandArray.size() - 1;
    }

    TAG_CommandState Update()   // 更新処理
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->m_display = false;
        }

        if (Input::IsPress(UP))     // 上アローキーを押されたとき
        {
            index++;
            if (index >= m_pCommandArray.size())
            {
                index = m_pCommandArray.size() - 1;
            }
        }
        if (Input::IsPress(DOWN))   // 下アローキーを押されたとき
        {
            index--;
            if (index < 0)
            {
                index = 0;
            }
        }

        return m_pCommandArray[index]->Execute();
    }

    void Draw()     // 描画処理
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->Draw(975 - (80 * i));
        }
    }

    void SetCommand(Command* _command)  // 生成されたコマンドを格納する
    {
        m_pCommandArray.push_back(_command);
    }
private:
    std::vector<Command*> m_pCommandArray;  // コマンド格納配列
    int index;                              // コマンド番号
};