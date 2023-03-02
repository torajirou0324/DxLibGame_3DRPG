//-----------------------------------------------------------------------------
// @brief  矢印描画用プロトタイプ宣言ヘッダー.
//-----------------------------------------------------------------------------
#pragma once

// 縦向きの矢印描画
void DrawArrowVertical(int posX, int posY);
// 横向きの矢印描画
void DrawArrowSide(int posX, int posY);
// 矢印の微動処理
void ArrowUpdate();

// フェードアウトイン
void FadeInInit();
void FadeOutInit();
void FadeDraw();