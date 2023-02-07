//-----------------------------------------------------------------------------
// @brief  矢印描画用プロトタイプ宣言処理.
//-----------------------------------------------------------------------------
#include <DxLib.h>
#include "ArrowSymbol.h"
#include "AssetManager.h"

//-----------------------------------------------------------------------------
// @brief  縦向きの矢印描画処理.
//-----------------------------------------------------------------------------
void DrawArrowVertical(int posX, int posY)
{
	DrawGraph(posX, posY, AssetManager::UseImage(AssetManager::DownArrow), TRUE);
}

//-----------------------------------------------------------------------------
// @brief  横向きの矢印処理.
//-----------------------------------------------------------------------------
void DrawArrowSide(int posX, int posY)
{
    DrawGraph(posX, posY, AssetManager::UseImage(AssetManager::RightArrow), TRUE);
}

void ArrowUpdate()
{
}
