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

    void Init(std::string name, int level, VECTOR position);     // ����������.
    void Update();  // �X�V����.
    void Draw();    // �`�揈��.
    void Animation();		// �A�j���[�V��������.

private:
};