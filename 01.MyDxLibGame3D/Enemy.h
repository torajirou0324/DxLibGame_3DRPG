//-----------------------------------------------------------------------------
// @brief  �G�l�~�[�N���X.
//-----------------------------------------------------------------------------
#pragma once

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
public:
    Enemy();        // �R���X�g���N�^.
    ~Enemy();       // �f�X�g���N�^.

    void Init(std::string name, int level);     // ����������.
    void Update();  // �X�V����.
    void Draw();    // �`�揈��.

private:
};