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
	int m_TitleHandle;			// ゲームタイトル画像のモデルハンドル.
	int m_arrowBesideHandle;	// コマンド選択横矢印のモデルハンドル.
	int m_arrowVerticalHandle;	// コマンド選択縦矢印のモデルハンドル.
	int m_arrowPosX;			// コマンド選択矢印のX座標.
	int m_arrowPosY;
	int m_BlackWindow;
	int m_intervalNum;
	int m_addNum;

	bool m_playFlag;
	bool m_nameSettingFlag;
};