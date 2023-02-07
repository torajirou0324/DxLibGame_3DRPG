//-----------------------------------------------------------------------------
// @brief  �^�C�g���V�[���N���X.
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
	int m_TitleHandle;			// �Q�[���^�C�g���摜�̃��f���n���h��.
	int m_playerHandle;			// �v���C���[�̃��f���n���h��.
	float m_animTime;			// ���݂̃A�j���[�V�������ԕۑ��p�i�[�p.
	float m_animTotalTime;		// �A�j���[�V�����̑��Đ�����.
	int m_BlackWindow;

	int m_arrowBesideHandle;	// �R�}���h�I�������̃��f���n���h��.
	int m_arrowVerticalHandle;	// �R�}���h�I���c���̃��f���n���h��.
	int m_arrowPosX;			// �R�}���h�I�����X���W.
	int m_arrowPosY;			// �R�}���h�I�����Y���W.
	int m_intervalNum;
	int m_addNum;

	bool m_playFlag;
	bool m_nameSettingFlag;

	VECTOR m_cameraPos;
	VECTOR m_targetPos;
};