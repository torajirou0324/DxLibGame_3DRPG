//-----------------------------------------------------------------------------
// @brief  タイトルシーンクラス.
//-----------------------------------------------------------------------------
#pragma once
#include <DxLib.h>
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
	int m_arrowPosY;			// コマンド選択矢印のY座標.
	int m_playerHandle;			// プレイヤーのモデルハンドル.
	float m_animTime;				// 現在のアニメーション時間保存用格納用.
	float m_animTotalTime;		// アニメーションの総再生時間.
	int m_BlackWindow;
	int m_intervalNum;
	int m_addNum;

	bool m_playFlag;
	bool m_nameSettingFlag;

	VECTOR m_cameraPos;
	VECTOR m_targetPos;
};