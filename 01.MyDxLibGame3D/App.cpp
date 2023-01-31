//-----------------------------------------------------------------------------
// @brief  �A�v���P�[�V�����N���X.
//-----------------------------------------------------------------------------
#include "App.h"
#include <DxLib.h>
#include "SceneManager.h"

App::App()
	: m_sceneManager(nullptr)
{
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1920, 1080, 16);
	ChangeWindowMode(TRUE);
	SetWaitVSyncFlag(TRUE);
	SetOutApplicationLogValidFlag(FALSE); // Log.txt�������o���Ȃ��悤�ɂ���
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();
	SetMainWindowText("RPG");
	SetBackgroundColor(250, 250, 250);
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(FALSE);

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);

	m_sceneManager = new SceneManager;
	m_sceneManager->SetNowScene(TAG_SCENE::TAG_TITLE);
}

App::~App()
{
	delete m_sceneManager;
	m_sceneManager = nullptr;

	// �c�w���C�u�����̌�n��
	DxLib_End();
}

void App::GameLoop()
{
	m_sceneManager->GameLoop();
}
