//-----------------------------------------------------------------------------
// @brief  エネミークラス.
//-----------------------------------------------------------------------------
#pragma once

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
public:
    Enemy();        // コンストラクタ.
    ~Enemy();       // デストラクタ.

    void Update();  // 更新処理.
    void Draw();    // 描画処理.



    void Damage(int atk)    // エネミー被ダメ処理
    {
        int HP = m_status.HP;
        HP = HP - atk;
        if (HP < 0)
        {
            HP = 0;
        }
        m_status.HP = HP;
    }


private:
};