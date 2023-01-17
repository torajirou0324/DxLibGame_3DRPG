//-----------------------------------------------------------------------------
// @brief  タイトルシーンクラス.
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
	int m_arrowHandle;		// コマンド選択矢印のモデルハンドル.
	int m_arrowPosX;		// コマンド選択矢印のX座標.

	bool m_playFlag;
};