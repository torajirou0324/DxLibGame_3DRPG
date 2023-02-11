//-----------------------------------------------------------------------------
// @brief  バトルイベントの戦闘開始処理クラス.
//-----------------------------------------------------------------------------
#include "BattleStart.h"
#include "Input.h"
#include "ArrowSymbol.h"
#include "PlayScene.h"

const int m_waitMaxTime = 40;		// 画面待機時間.
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
BattleStart::BattleStart(class PlayScene* _playScene)
    : m_waitTimer(0)
{
    m_pPlaySceneStorage = _playScene;
    gaussianScreen = MakeScreen(1920, 1080);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
BattleStart::~BattleStart()
{
    DeleteGraph(gaussianScreen);
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void BattleStart::Init()
{
    m_waitTimer = 0;
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_BattleState BattleStart::Update()
{
    m_waitTimer++;

    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::CommandProcess;
    }

    return TAG_BattleState::None;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void BattleStart::Draw()
{
    printfDx("バトル開始処理");

    auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
    for (int i = 1; i < CharacterALL.size(); i++)       // 敵が現れたことを画面で伝える
    {
        DrawFormatString(650, 740 + 60 * i, GetColor(255, 255, 255), "%sが現れた", CharacterALL[i]->GetName().c_str());
    }
    if (m_waitTimer < m_waitMaxTime)                    // 画面ぼかし
    {
        GetDrawScreenGraph(0, 0, 1920, 1080, gaussianScreen);
        GraphFilter(gaussianScreen, DX_GRAPH_FILTER_GAUSS, 16, 1400);
        DrawGraph(0, 0, gaussianScreen, TRUE);
    }

    DrawArrowVertical(1240, 950);      // 矢印の表示
}
