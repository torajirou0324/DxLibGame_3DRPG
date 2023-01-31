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

    void Init(std::string name, int level);    // 初期化処理.
    void Update();  // 更新処理.
    void Draw();    // 描画処理.

    // セッター
    void SetAllStatus(const Status& _status) { m_status = _status; }
    // ゲッター
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_status; }
private:
};