//-----------------------------------------------------------------------------
// @brief  �G�l�~�[�N���X.
//-----------------------------------------------------------------------------
#pragma once

#include <DxLib.h>
#include "Status.h"

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Update();
    void Draw();

    // �Z�b�^�[
    void SetAllStatus(const Status& _status) { m_enemyStatus = _status; }
    // �Q�b�^�[
    const Status& GetAllStatus() const { return m_enemyStatus; }
private:
    int m_modelHandle;

    VECTOR m_position;

    Status m_enemyStatus;


};