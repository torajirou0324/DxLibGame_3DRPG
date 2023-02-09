//-----------------------------------------------------------------------------
// @brief  �V�[���Ǘ��N���X.
//-----------------------------------------------------------------------------
#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "Player.h"
#include "Field.h"
#include "Input.h"
#include "ArrowSymbol.h"
#include "DebugDrawGrid.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
SceneManager::SceneManager()
	: m_nowScene(nullptr)
{
	Field::CreateInstance();
	Input::CreateInstance();
	SetFontSize(64);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	ClearScene();
	Field::DeleteInstance();
	Input::DeleteInstance();
}

//-----------------------------------------------------------------------------
// @brief  �Q�[�����[�v����.
//-----------------------------------------------------------------------------
void SceneManager::GameLoop()
{
	while (ProcessMessage() == 0 && Input::IsPressed(TYPE::ESCAPE) == 0)
	{
		Input::Update();
		ArrowUpdate();
		auto tag = m_nowScene->Update();

#ifdef _DEBUG
		//DrawGrid(1000.0f, 30);
#endif // _DEBUG

		{
			ClearDrawScreen();

			clsDx();
			m_nowScene->Draw();

			ScreenFlip();
		}

		if (tag == TAG_SCENE::TAG_NONE)
		{
			continue;
		}
		if (tag == TAG_SCENE::TAG_ESCAPE)
		{
			break;
		}

		ClearScene();
		SetNowScene(tag);
	}
}

//-----------------------------------------------------------------------------
// @brief  ���݂̃V�[�����Z�b�g.
//-----------------------------------------------------------------------------
void SceneManager::SetNowScene(const TAG_SCENE& tag)
{
	switch (tag)
	{
	case TAG_SCENE::TAG_TITLE:
		m_nowScene = new TitleScene;
		break;
	case TAG_SCENE::TAG_PLAY:
		m_nowScene = new PlayScene;
		break;
	case TAG_SCENE::TAG_END:
		m_nowScene = new EndScene;
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// @brief  ���݂̃V�[�������.
//-----------------------------------------------------------------------------
void SceneManager::ClearScene()
{
	if (m_nowScene != nullptr)
	{
		delete m_nowScene;
		m_nowScene = nullptr;
	}
}
