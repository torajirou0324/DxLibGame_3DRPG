//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̐퓬�J�n�����N���X.
//-----------------------------------------------------------------------------
#include "BattleStart.h"
#include "Input.h"
#include "ArrowSymbol.h"
#include "PlayScene.h"

const int m_waitMaxTime = 40;		// ��ʑҋ@����.
//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
BattleStart::BattleStart()
    : m_waitTimer(0)
    , m_arrowMoveNum(0)		// �R�}���h�I����̔���������p�ϐ�.
    , m_intervalNum(0)
{
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
void BattleStart::Init(std::vector<Character*>& character, Character*& attackNowCharacter, PlayScene* playScene)
{
    m_pCharacter = character;
    m_pCharacterAttackNow = attackNowCharacter;
    m_pPlayScene = playScene;
    m_waitTimer = 0;
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_BattleState BattleStart::Update()
{
    m_waitTimer++;

    m_intervalNum++;
    if (m_intervalNum > 7)
    {
        m_intervalNum = 0;
        m_arrowMoveNum++;
        if (m_arrowMoveNum > 20)
        {
            m_arrowMoveNum = 0;
        }
    }
    if (Input::IsPress(ENTER))
    {
        return TAG_BattleState::Command;
    }

    return TAG_BattleState::None;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void BattleStart::Draw()
{
    printfDx("�o�g���J�n����");

    for (int i = 1; i < m_pCharacter.size(); i++)       // �G�����ꂽ���Ƃ���ʂœ`����
    {
        DrawFormatString(650, 740 + 60 * i, GetColor(255, 255, 255), "%s�����ꂽ", m_pCharacter[i]->GetName().c_str());
    }
    if (m_waitTimer < m_waitMaxTime)                    // ��ʂڂ���
    {
        GetDrawScreenGraph(0, 0, 1920, 1080, gaussianScreen);
        GraphFilter(gaussianScreen, DX_GRAPH_FILTER_GAUSS, 16, 1400);
        DrawGraph(0, 0, gaussianScreen, TRUE);
    }

    DrawArrowVertical(1240, 950 + m_arrowMoveNum);      // ���̕\��
}
