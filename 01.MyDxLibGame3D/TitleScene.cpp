//-----------------------------------------------------------------------------
// @brief  �^�C�g���V�[���N���X.
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include "Field.h"
#include "Input.h"
#include "AssetManager.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
TitleScene::TitleScene()
	: m_intervalNum(0)
	, m_addNum(0)
{
	// �^�C�g���V�[���Ɏg���A�Z�b�g���A�Z�b�g�}�l�[�W���[������炤
	m_TitleHandle = AssetManager::UseImage(AssetManager::Title);
	m_arrowBesideHandle = AssetManager::UseImage(AssetManager::RightArrow);
	m_arrowVerticalHandle = AssetManager::UseImage(AssetManager::DownArrow);
	m_BlackWindow = AssetManager::UseImage(AssetManager::BlackWindow);
	m_arrowPosX = 500;
	m_arrowPosY = 640;
	m_playFlag = true;
	m_nameSettingFlag = false;
	m_playerHandle = AssetManager::UseModel(AssetManager::Player);
	int GraphHandle = AssetManager::UseImage(AssetManager::PlayerTexture1);
	MV1SetTextureGraphHandle(m_playerHandle, 0, GraphHandle, TRUE);
	// �v���C���[���f���̑傫���ƍ��W���Z�b�g
	MV1SetScale(m_playerHandle, VGet(0.3f, 0.3f, 0.3f));
	MV1SetPosition(m_playerHandle, VGet(0.0f, 0.0f, 0.0f));

	// �����ɍ��킹�ă��f����]
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(VGet(0.0f,0.0f,1.0f), rotYMat);

	// ���f���ɉ�]���Z�b�g����
	MV1SetRotationZYAxis(m_playerHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// ���f����Animation���Z�b�g
	MV1DetachAnim(m_playerHandle, 0);
	auto attachIndex = MV1AttachAnim(m_playerHandle, 0, AssetManager::UseModel(AssetManager::AnimIdle));
	m_animTotalTime = MV1GetAnimTotalTime(AssetManager::UseModel(AssetManager::AnimIdle), attachIndex);
	m_animTime = 0.0f;

	// �J�����̃|�W�V�����ƖڕW��������
	m_cameraPos = VGet(5.0f, 30.0f, 10.0f);
	m_targetPos = VGet(5.0f, 32.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
TitleScene::~TitleScene()
{
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_SCENE TitleScene::Update()
{
	// �J�����̃|�W�V�����Z�b�g
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos); // pos(0.0f, 60.0f, -50.0f) target(0.0f,20.0f,20.0f)

	// �A�j���[�V�����J��Ԃ�����
	if (m_animTotalTime < m_animTime)
	{
		m_animTime = 0.0f;
	}

	// ���݂̃A�j���[�V�����t���[�������f���ɃA�^�b�`����
	MV1SetAttachAnimTime(m_playerHandle, 0, m_animTime);

	// �A�j���[�V�����t���[�����Z
	m_animTime += 0.3f;

	if (Input::IsPress(LEFT))
	{
		m_arrowPosX = 150;
		m_playFlag = false;
	}
	if (Input::IsPress(RIGHT))
	{
		m_arrowPosX = 500;
		m_playFlag = true;
	}

	if (m_nameSettingFlag)
	{
		if (Input::IsPress(ENTER))
		{
			return TAG_SCENE::TAG_PLAY;
		}
	}

	if (m_playFlag && Input::IsPress(ENTER))
	{
		m_nameSettingFlag = true;
		m_arrowPosX = 980;
		m_arrowPosY = 920;
		SetFontSize(35);
	}

	if (!m_playFlag && Input::IsPress(ENTER))
	{
		return TAG_SCENE::TAG_ESCAPE;
	}

	m_intervalNum++;
	if (m_intervalNum > 7)
	{
		m_intervalNum = 0;
		m_addNum++;
		if (m_addNum > 20)
		{
			m_addNum = 0;
		}
	}

	return TAG_SCENE::TAG_NONE;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void TitleScene::Draw()
{
	//printfDx("TitleScene\n");
	Field::DrawCall();
	MV1DrawModel(m_playerHandle);
	DrawGraph(100, 420, m_TitleHandle, TRUE);
	if (!m_nameSettingFlag)
	{
		DrawFormatString(250, 630, GetColor(255, 255, 255), "�����");
		DrawFormatString(600, 630, GetColor(255, 255, 255), "�͂��߂�");

		DrawGraph(m_arrowPosX + m_addNum, m_arrowPosY, m_arrowBesideHandle, TRUE);
	}
	else
	{
		DrawExtendGraph(100, 700, 1060, 1000, m_BlackWindow, TRUE);
		DrawFormatString(150, 760, GetColor(255, 255, 255), "���Ȃ��� �L�c�L �C�`�J \n3�ʁ{�{�X����������_���W����\n�X�L�����g�������X�^�[��|���Đ�����\n�{�X���������ƃQ�[���N���A");
		DrawGraph(m_arrowPosX, m_arrowPosY + m_addNum, m_arrowVerticalHandle, TRUE);
	}

}
