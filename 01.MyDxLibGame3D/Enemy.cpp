//-----------------------------------------------------------------------------
// @brief  �G�l�~�[�N���X.
//-----------------------------------------------------------------------------
#include "Enemy.h"
#include <DxLib.h>
#include "Player.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Enemy::Enemy()
{
    m_modelHandle = MV1LoadModel("data/enemy/Deamon.mv1");
    m_position = Player::GetPlayerPosition();
    // �����ɍ��킹�ă��f����]
    MATRIX rotYMat = MGetRotY(DX_PI_F / 180.0f);
    VECTOR aimVec = VTransform(Player::GetDir(), rotYMat);

    // ���f���ɉ�]���Z�b�g����
    MV1SetRotationZYAxis(m_modelHandle, aimVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(m_modelHandle, m_position);
    // ���f���̑傫�����Z�b�g
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
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
Enemy::~Enemy()
{
    MV1DeleteModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void Enemy::Init(std::string name, int level)
{
    m_name = name;

    m_enemyStatus.LV = level;
    m_enemyStatus.HP = 10 + 2 * level;
    m_enemyStatus.ATK = 3 + 1 * level;
    m_enemyStatus.AGL = 2 + 1 * level;
    m_enemyStatus.EXP = level;

    m_position = Player::GetPlayerPosition();
    // �����ɍ��킹�ă��f����]
    MATRIX rotYMat = MGetRotY(DX_PI_F / 180.0f);
    VECTOR aimVec = VTransform(Player::GetDir(), rotYMat);

    // ���f���ɉ�]���Z�b�g����
    MV1SetRotationZYAxis(m_modelHandle, aimVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(m_modelHandle, m_position);
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void Enemy::Update()
{
    
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void Enemy::Draw()
{
    MV1DrawModel(m_modelHandle);
}
