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

    void Init(std::string name, int level);     // 初期化処理.
    void Update();  // 更新処理.
    void Draw();    // 描画処理.

private:
};