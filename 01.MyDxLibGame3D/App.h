//-----------------------------------------------------------------------------
// @brief  �A�v���P�[�V�����N���X.
//-----------------------------------------------------------------------------
#pragma once
class SceneManager;

class App
{
public:
	App();
	~App();

	void GameLoop();

private:
	SceneManager* m_sceneManager;
};