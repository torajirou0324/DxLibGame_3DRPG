//-----------------------------------------------------------------------------
// @brief  デーモンクラス.
//-----------------------------------------------------------------------------
#include "Deamon.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Deamon::Deamon()
{
    m_modelHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::Deamon));
    // 向きに合わせてモデル回転

    // ３Dモデルのポジション設定
    MV1SetPosition(m_modelHandle, m_position);
    // モデルの大きさをセット
    MV1SetScale(m_modelHandle, VGet(0.2f, 0.20f, 0.2f));

    int GraphHandle1 = AssetManager::UseImage(AssetManager::DeamonTexture1);
    int GraphHandle2 = AssetManager::UseImage(AssetManager::DeamonTexture2);
    int GraphHandle3 = AssetManager::UseImage(AssetManager::DeamonTexture3);
    MV1SetTextureGraphHandle(m_modelHandle, 0, GraphHandle1, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 1, GraphHandle2, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 2, GraphHandle3, TRUE);

    // アニメーションの初期化
    MV1DetachAnim(m_modelHandle, 0);
    auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
    m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
    m_animTime = 0.0f;
    m_beforeAnimType = m_animType;

    m_status.LV = 0;
    m_status.HP = 0;
    m_status.ATK = 0;
    m_status.AGL = 0;
    m_status.EXP = 0;

    m_name = "デーモン";
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
    Animation();
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void Deamon::Draw()
{
    MV1DrawModel(m_modelHandle);
}

void Deamon::Move()
{
    Attack();
}
