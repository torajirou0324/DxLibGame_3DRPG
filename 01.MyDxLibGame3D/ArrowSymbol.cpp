//-----------------------------------------------------------------------------
// @brief  ���`��p�v���g�^�C�v�錾����.
//-----------------------------------------------------------------------------
#include <DxLib.h>
#include "ArrowSymbol.h"
#include "AssetManager.h"

int m_arrowMoveNum(0);		// �R�}���h�I����̔���������p�ϐ�.
int m_intervalNum(0);
int m_fadeNum(0);
int m_fadeAddNum(0);

//-----------------------------------------------------------------------------
// @brief  �c�����̖��`�揈��.
//-----------------------------------------------------------------------------
void DrawArrowVertical(int posX, int posY)
{
	DrawGraph(posX, posY + m_arrowMoveNum, AssetManager::UseImage(AssetManager::DownArrow), TRUE);
}

//-----------------------------------------------------------------------------
// @brief  �������̖�󏈗�.
//-----------------------------------------------------------------------------
void DrawArrowSide(int posX, int posY)
{
    DrawGraph(posX + m_arrowMoveNum, posY, AssetManager::UseImage(AssetManager::RightArrow), TRUE);
}

void ArrowUpdate()
{
    if (m_intervalNum > 7)
    {
        m_intervalNum = 0;
        m_arrowMoveNum++;
        if (m_arrowMoveNum > 20)
        {
            m_arrowMoveNum = 0;
        }
    }
    m_intervalNum++;
    m_fadeNum = m_fadeNum + m_fadeAddNum;
    if (m_fadeNum < 0) { m_fadeNum = 0; }
    if (m_fadeNum > 255) { m_fadeNum = 255; }
}

void FadeInInit()
{
    m_fadeAddNum = 1;
}

void FadeOutInit()
{
    m_fadeAddNum = -1;
}

void FadeDraw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeNum);
    DrawExtendGraph(-100, -150, 2030, 2090, AssetManager::UseImage(AssetManager::BlackWindow), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
