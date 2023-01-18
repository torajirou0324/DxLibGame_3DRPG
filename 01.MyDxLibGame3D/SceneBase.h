//-----------------------------------------------------------------------------
// @brief  シーンの基底クラス.
//-----------------------------------------------------------------------------
#pragma once

enum class TAG_SCENE
{
	TAG_TITLE,
	TAG_PLAY,
	TAG_END,
	TAG_ESCAPE,

	TAG_NONE
};

class Scene
{
public:
	Scene(){}
	virtual ~Scene(){}

	virtual TAG_SCENE Update() = 0;
	virtual void Draw() = 0;
};