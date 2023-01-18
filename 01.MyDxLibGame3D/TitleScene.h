//-----------------------------------------------------------------------------
// @brief  �^�C�g���V�[���N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "SceneBase.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
	int m_TitleCommand;
	int m_arrowHandle;		// �R�}���h�I����̃��f���n���h��.
	int m_arrowPosX;		// �R�}���h�I�����X���W.

	bool m_playFlag;
};