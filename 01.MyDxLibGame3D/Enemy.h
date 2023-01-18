//-----------------------------------------------------------------------------
// @brief  エネミークラス.
//-----------------------------------------------------------------------------
#pragma once

#include "Status.h"

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Update();
    void Draw();

    // セッター
    void SetAllStatus(const Status& _status) { m_enemyStatus = _status; }
    // ゲッター
    const Status& GetAllStatus() const { return m_enemyStatus; }
private:
    Status m_enemyStatus;


};