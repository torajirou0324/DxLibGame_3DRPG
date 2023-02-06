//-----------------------------------------------------------------------------
// @brief  エネミークラス.
//-----------------------------------------------------------------------------
#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy();        // コンストラクタ.
    ~Enemy();       // デストラクタ.

    void Init(std::string name, int level, VECTOR position);     // 初期化処理.
    void Update();  // 更新処理.
    void Draw();    // 描画処理.
    void Animation();		// アニメーション処理.

private:
};