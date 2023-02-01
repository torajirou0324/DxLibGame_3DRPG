//-----------------------------------------------------------------------------
// @brief  デーモンクラス.
//-----------------------------------------------------------------------------
#include "Deamon.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Deamon::Deamon()
{
    m_modelHandle = AssetManager::UseModel(AssetManager::Deamon);
    // 向きに合わせてモデル回転

    // ３Dモデルのポジション設定
    MV1SetPosition(m_modelHandle, m_position);
    // モデルの大きさをセット
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
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Deamon::~Deamon()
{
    MV1DeleteModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void Deamon::Update()
{
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void Deamon::Draw()
{
    MV1DrawModel(m_modelHandle);
}
