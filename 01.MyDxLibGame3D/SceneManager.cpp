//-----------------------------------------------------------------------------
// @brief  シーン管理クラス.
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
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
SceneManager::SceneManager()
	: m_nowScene(nullptr)
{
	Field::CreateInstance();
	Input::CreateInstance();
	SetFontSize(64);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	ClearScene();
	Field::DeleteInstance();
	Input::DeleteInstance();
}

//-----------------------------------------------------------------------------
// @brief  ゲームループ処理.
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
// @brief  現在のシーンをセット.
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
// @brief  現在のシーンを解放.
//-----------------------------------------------------------------------------
void SceneManager::ClearScene()
{
	if (m_nowScene != nullptr)
	{
		delete m_nowScene;
		m_nowScene = nullptr;
	}
}
