//-----------------------------------------------------------------------------
// @brief  エネミークラス.
//-----------------------------------------------------------------------------
#include "Enemy.h"
#include <DxLib.h>
#include "Player.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Enemy::Enemy()
{
    m_modelHandle = MV1LoadModel("data/enemy/Deamon.mv1");
    m_position = Player::GetPlayerPosition();
    // 向きに合わせてモデル回転
    MATRIX rotYMat = MGetRotY(DX_PI_F / 180.0f);
    VECTOR aimVec = VTransform(Player::GetDir(), rotYMat);

    // モデルに回転をセットする
    MV1SetRotationZYAxis(m_modelHandle, aimVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    // ３Dモデルのポジション設定
    MV1SetPosition(m_modelHandle, m_position);
    // モデルの大きさをセット
    MV1SetScale(m_modelHandle, VGet(0.2f, 0.2f, 0.2f));

    int GraphHandle1 = LoadGraph("data/enemy/Demon1.png");
    int GraphHandle2 = LoadGraph("data/enemy/Demon2.png");
    int GraphHandle3 = LoadGraph("data/enemy/Demon3.png");
    MV1SetTextureGraphHandle(m_modelHandle, 0, GraphHandle1, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 1, GraphHandle2, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 2, GraphHandle3, TRUE);

    m_enemyStatus.LV = 1;
    m_enemyStatus.HP = 10;
    m_enemyStatus.ATK = 4;
    m_enemyStatus.AGL = 3;
    m_enemyStatus.EXP = 1;
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Enemy::~Enemy()
{
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void Enemy::Update()
{
    
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void Enemy::Draw()
{
    MV1DrawModel(m_modelHandle);
}
