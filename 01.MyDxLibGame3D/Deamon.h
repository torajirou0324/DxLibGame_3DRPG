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

    void Init(std::string name, int level);     // ����������.
    void Update()override;                      // �X�V����.
    void Draw()override;                        // �`�揈��.

private:

};