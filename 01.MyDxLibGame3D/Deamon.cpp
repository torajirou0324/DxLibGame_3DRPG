//-----------------------------------------------------------------------------
// @brief  デーモンクラス.
//-----------------------------------------------------------------------------
#include "Deamon.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Deamon::Deamon()
{
    m_modelHandle = MV1LoadModel("data/enemy/Deamon.mv1");
    // 向きに合わせてモデル回転

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
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void Deamon::Init(std::string name, int level)
{
    m_name = name;

    m_status.LV = level;
    m_status.HP = 10 + 2 * level;
    m_status.ATK = 3 + 1 * level;
    m_status.AGL = 2 + 1 * level;
    m_status.EXP = level;

    // ３Dモデルのポジション設定
    MV1SetPosition(m_modelHandle, m_position);
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
