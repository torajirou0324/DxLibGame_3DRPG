//-----------------------------------------------------------------------------
// @brief  バトルのコマンド選択管理クラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Command.h"

class BattleCommandManager
{
public:
    // デストラクタ
    ~BattleCommandManager()
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            delete m_pCommandArray[i];
            m_pCommandArray[i] = nullptr;
        }
        m_pCommandArray.clear();
    }

    // 共通の初期化処理
    void Init()
    {
        index = m_pCommandArray.size() - 1;
    }

    // 技のみの初期化処理
    void Init(const SKILL* _skillStorage)
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            SKILL skill = _skillStorage[i];
            m_pCommandArray[i]->Init(skill);
        }
    }

    // 攻撃目標のみの初期化処理
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

    // 更新処理
    TAG_CommandState Update()
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

    // 描画処理
    void Draw()
    {
        for (int i = 0; i < m_pCommandArray.size(); i++)
        {
            m_pCommandArray[i]->Draw(955 - (80 * i));
        }
    }

    // 生成されたコマンドを格納する
    void SetCommand(Command* _command)
    {
        m_pCommandArray.push_back(_command);
    }
private:
    std::vector<Command*> m_pCommandArray;  // コマンド格納配列
    int index;                              // コマンド番号
};