//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̐퓬�J�n�����N���X.
//-----------------------------------------------------------------------------
#include "BattleStart.h"
#include "Input.h"
#include "PlayScene.h"

const int m_waitMaxTime = 40;		// ��ʑҋ@����.
//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleStart::BattleStart(class PlayScene* _playScene)
    : m_waitTimer(0)
{
    m_pPlaySceneStorage = _playScene;
    gaussianScreen = MakeScreen(1920, 1080);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
BattleStart::~BattleStart()
{
    DeleteGraph(gaussianScreen);
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void BattleStart::Init()
{
    m_waitTimer = 0;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
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
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleStart::Draw()
{
    printfDx("�o�g���J�n����");

    auto CharacterALL = m_pPlaySceneStorage->GetCharacterArrayAddress();
    for (int i = 1; i < CharacterALL.size(); i++)       // �G�����ꂽ���Ƃ���ʂœ`����
    {
        DrawFormatString(650, 740 + 60 * i, GetColor(255, 255, 255), "%s�����ꂽ", CharacterALL[i]->GetName().c_str());
    }
    if (m_waitTimer < m_waitMaxTime)                    // ��ʂڂ���
    {
        GetDrawScreenGraph(0, 0, 1920, 1080, gaussianScreen);
        GraphFilter(gaussianScreen, DX_GRAPH_FILTER_GAUSS, 16, 1400);
        DrawGraph(0, 0, gaussianScreen, TRUE);
    }

    DrawArrowVertical(1240, 950);      // ���̕\��
}
