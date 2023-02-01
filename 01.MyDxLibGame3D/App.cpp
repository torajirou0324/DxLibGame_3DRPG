//-----------------------------------------------------------------------------
// @brief  �A�v���P�[�V�����N���X.
//-----------------------------------------------------------------------------
#include "App.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "AssetManager.h"

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

	// �g�p����A�Z�b�g�����O�ɓǂݍ���
	AssetManager::LoadImage(AssetManager::Title, "data/Title/Title.png");
	AssetManager::LoadImage(AssetManager::RightArrow, "data/comand/RightArrow.png");
	AssetManager::LoadImage(AssetManager::DownArrow, "data/comand/DownArrow.png");
	AssetManager::LoadImage(AssetManager::BlackWindow, "data/comand/BlackWindow.png");
	AssetManager::LoadImage(AssetManager::CommandWindowWhite, "data/comand/commandWindowWhite.png");
	AssetManager::LoadImage(AssetManager::CommandWindowBlack, "data/comand/commandWindowBlack.png");
	AssetManager::LoadImage(AssetManager::StatusWindow, "data/comand/StatusWindow.png");
	AssetManager::LoadImage(AssetManager::MapTile, "data/model/pool/MapTile.png");
	AssetManager::LoadImage(AssetManager::PlayerTexture1, "data/player/playertex.png");
	AssetManager::LoadImage(AssetManager::PlayerTexture2, "data/player/playertex1.png");
	AssetManager::LoadImage(AssetManager::PlayerTexture3, "data/player/playertex2.png");
	AssetManager::LoadImage(AssetManager::PlayerTexture4, "data/player/playertex3.png");
	AssetManager::LoadImage(AssetManager::DeamonTexture1, "data/enemy/Deamon/Demon1.png");
	AssetManager::LoadImage(AssetManager::DeamonTexture2, "data/enemy/Deamon/Demon2.png");
	AssetManager::LoadImage(AssetManager::DeamonTexture3, "data/enemy/Deamon/Demon3.png");	// �������܂ŉ摜

	AssetManager::LoadModel(AssetManager::Field, "data/staticObje/Field.mv1");
	AssetManager::LoadModel(AssetManager::Wall, "data/staticObje/Wall.mv1");
	AssetManager::LoadModel(AssetManager::Player, "data/player/Player.mv1");
	AssetManager::LoadModel(AssetManager::Deamon, "data/enemy/Deamon/Deamon.mv1");
	AssetManager::LoadModel(AssetManager::AnimAttack, "data/player/animAttack.mv1");
	AssetManager::LoadModel(AssetManager::AnimDamage, "data/player/animDamage.mv1");
	AssetManager::LoadModel(AssetManager::AnimDeath, "data/player/animDeath.mv1");
	AssetManager::LoadModel(AssetManager::AnimIdle, "data/player/animIdle.mv1");
	AssetManager::LoadModel(AssetManager::AnimWalk, "data/player/animWalk.mv1");		// �������܂�3D���f���܂��̓A�j���[�V����

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);

	m_sceneManager = new SceneManager;
	m_sceneManager->SetNowScene(TAG_SCENE::TAG_TITLE);
}

App::~App()
{
	AssetManager::Terminate();
	delete m_sceneManager;
	m_sceneManager = nullptr;

	// �c�w���C�u�����̌�n��
	DxLib_End();
}

void App::GameLoop()
{
	m_sceneManager->GameLoop();
}
