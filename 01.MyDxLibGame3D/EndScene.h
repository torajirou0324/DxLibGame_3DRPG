//-----------------------------------------------------------------------------
// @brief  �G���h�V�[���N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "SceneBase.h"

class EndScene : public Scene
{
public:
	EndScene();
	~EndScene() override;

	TAG_SCENE Update() override;
	void Draw() override;
};