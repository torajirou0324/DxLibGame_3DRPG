//-----------------------------------------------------------------------------
// @brief  �G�l�~�[�N���X.
//-----------------------------------------------------------------------------
#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy();        // �R���X�g���N�^.
    ~Enemy();       // �f�X�g���N�^.

    void Init(std::string name, int level);    // ����������.
    void Update();  // �X�V����.
    void Draw();    // �`�揈��.

    // �Z�b�^�[
    void SetAllStatus(const Status& _status) { m_status = _status; }
    // �Q�b�^�[
    const std::string& GetName() const { return m_name; }
    const Status& GetAllStatus() const { return m_status; }
private:
};