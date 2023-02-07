//-----------------------------------------------------------------------------
// @brief  ���`��p�v���g�^�C�v�錾����.
//-----------------------------------------------------------------------------
#include <DxLib.h>
#include "ArrowSymbol.h"
#include "AssetManager.h"

//-----------------------------------------------------------------------------
// @brief  �c�����̖��`�揈��.
//-----------------------------------------------------------------------------
void DrawArrowVertical(int posX, int posY)
{
	DrawGraph(posX, posY, AssetManager::UseImage(AssetManager::DownArrow), TRUE);
}

//-----------------------------------------------------------------------------
// @brief  �������̖�󏈗�.
//-----------------------------------------------------------------------------
void DrawArrowSide(int posX, int posY)
{
    DrawGraph(posX, posY, AssetManager::UseImage(AssetManager::RightArrow), TRUE);
}

void ArrowUpdate()
{
}
