//-----------------------------------------------------------------------------
// @brief  エネミークラス.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <DxLib.h>
#include "Status.h"

class Enemy
{
public:
    Enemy();        // コンストラクタ.
    ~Enemy();       // デストラクタ.

    void Init(std::string name, int level);    // 初期化処理.
    void Update();  // 更新処理.
    void Draw();    // 描画処理.

    // セッター
    void SetAllStatus(const Status& _status) { m_enemyStatus = _status; }
    // ゲッター
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_enemyStatus; }
private:
    int m_modelHandle;      // エネミーのモデルハンドル

    std::string m_name;     // エネミーの名前

    VECTOR m_position;      // エネミーの座標

    Status m_enemyStatus;   // エネミーのステータス


};