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

    void Update();  // �X�V����.
    void Draw();    // �`�揈��.



    void Damage(int atk)    // �G�l�~�[��_������
    {
        int HP = m_status.HP;
        HP = HP - atk;
        if (HP < 0)
        {
            HP = 0;
        }
        m_status.HP = HP;
    }


private:
};