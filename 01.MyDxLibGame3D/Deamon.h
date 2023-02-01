//-----------------------------------------------------------------------------
// @brief  デーモンクラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Enemy.h"

class Deamon : public Enemy
{
public:
    Deamon();
    ~Deamon();

    void Update()override;                      // 更新処理.
    void Draw()override;                        // 描画処理.

private:

};