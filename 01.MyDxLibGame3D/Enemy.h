//-----------------------------------------------------------------------------
// @brief  �G�l�~�[�N���X.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <DxLib.h>
#include "Status.h"

class Enemy
{
public:
    Enemy();        // �R���X�g���N�^.
    ~Enemy();       // �f�X�g���N�^.

    void Init(std::string name, int level);    // ����������.
    void Update();  // �X�V����.
    void Draw();    // �`�揈��.

    // �Z�b�^�[
    void SetAllStatus(const Status& _status) { m_enemyStatus = _status; }
    // �Q�b�^�[
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_enemyStatus; }
private:
    int m_modelHandle;      // �G�l�~�[�̃��f���n���h��

    std::string m_name;     // �G�l�~�[�̖��O

    VECTOR m_position;      // �G�l�~�[�̍��W

    Status m_enemyStatus;   // �G�l�~�[�̃X�e�[�^�X


};