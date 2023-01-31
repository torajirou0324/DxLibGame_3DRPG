//-----------------------------------------------------------------------------
// @brief  �f�[�����N���X.
//-----------------------------------------------------------------------------
#include "Deamon.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Deamon::Deamon()
{
    m_modelHandle = MV1LoadModel("data/enemy/Deamon.mv1");
    // �����ɍ��킹�ă��f����]

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

    m_status.LV = 0;
    m_status.HP = 0;
    m_status.ATK = 0;
    m_status.AGL = 0;
    m_status.EXP = 0;
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
Deamon::~Deamon()
{
    MV1DeleteModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void Deamon::Init(std::string name, int level)
{
    m_name = name;

    m_status.LV = level;
    m_status.HP = 10 + 2 * level;
    m_status.ATK = 3 + 1 * level;
    m_status.AGL = 2 + 1 * level;
    m_status.EXP = level;

    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(m_modelHandle, m_position);
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void Deamon::Update()
{
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void Deamon::Draw()
{
    MV1DrawModel(m_modelHandle);
}
