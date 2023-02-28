//-----------------------------------------------------------------------------
// @brief  �m�[�}���C�x���g�Ǘ��N���X.
//-----------------------------------------------------------------------------
#pragma once
#include <functional>
#include <vector>
#include "WalkAroundEnemy.h"
#include "WallCollider.h"

class NormalEventManager
{
public:
    NormalEventManager(class Player* _player, std::function<void(bool, class WalkAroundEnemy*)> _func);
    ~NormalEventManager();

    void Init();
    void Update();
    void Draw();

private:
    std::function<void(bool, class WalkAroundEnemy*)> m_func;
    class Player* m_pPlayer;

    std::vector< WalkAroundEnemy*> m_pEnemyArray;

    std::vector<WallCollider*> m_pWallColliderArray;
};