//-----------------------------------------------------------------------------
// @brief  �f�[�����N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Enemy.h"

class Deamon : public Enemy
{
public:
    Deamon();
    ~Deamon();

    void Update();                      // �X�V����.
    void Draw()override;                        // �`�揈��.
    void Move() override;
    
private:

};