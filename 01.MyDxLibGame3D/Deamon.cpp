//-----------------------------------------------------------------------------
// @brief  �f�[�����N���X.
//-----------------------------------------------------------------------------
#include "Deamon.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Deamon::Deamon()
{
    m_modelHandle = AssetManager::UseModel(AssetManager::Deamon);
    // �����ɍ��킹�ă��f����]

    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(m_modelHandle, m_position);
    // ���f���̑傫�����Z�b�g
    MV1SetScale(m_modelHandle, VGet(0.2f, 0.2f, 0.2f));

    int GraphHandle1 = AssetManager::UseImage(AssetManager::DeamonTexture1);
    int GraphHandle2 = AssetManager::UseImage(AssetManager::DeamonTexture2);
    int GraphHandle3 = AssetManager::UseImage(AssetManager::DeamonTexture3);
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
