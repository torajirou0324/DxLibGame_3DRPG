//-----------------------------------------------------------------------------
// @brief  アプリケーションクラス.
//-----------------------------------------------------------------------------
#include "App.h"
#include <DxLib.h>
#include "SceneManager.h"

App::App()
	: m_sceneManager(nullptr)
{
	// 画面モードのセット
	SetGraphMode(1920, 1080, 16);
	ChangeWindowMode(TRUE);
	SetWaitVSyncFlag(TRUE);
	SetOutApplicationLogValidFlag(FALSE); // Log.txtを書き出さないようにする
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();
	SetMainWindowText("RPG");
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(FALSE);

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);

	m_sceneManager = new SceneManager;
	m_sceneManager->SetNowScene(TAG_SCENE::TAG_TITLE);
}

App::~App()
{
	delete m_sceneManager;
	m_sceneManager = nullptr;

	// ＤＸライブラリの後始末
	DxLib_End();
}

void App::GameLoop()
{
	m_sceneManager->GameLoop();
}
