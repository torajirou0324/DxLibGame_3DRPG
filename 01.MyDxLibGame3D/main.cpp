//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#include <DxLib.h>
#include "App.h"

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	App app;
	app.GameLoop();
	// ソフトの終了
	return 0;
}