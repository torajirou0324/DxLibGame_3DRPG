//-----------------------------------------------------------------------------
// @brief  �t�B�[���h�ɕ~���n�ʕ`��p�ÓI�N���X.
//-----------------------------------------------------------------------------
#include "Field.h"
#include <DxLib.h>

Field* Field::m_field = nullptr;

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Field::Field()
{
	m_modelHandle = MV1LoadModel("data/model/pool/Stadium.mv1");
	int GraphHandle = LoadGraph("data/model/pool/MapTile.png");
	MV1SetTextureGraphHandle(m_modelHandle, 0, GraphHandle, TRUE);
	MV1SetScale(m_modelHandle, VGet(5.0f, 1.0f, 6.0f));
	MV1SetMaterialDifColor(m_modelHandle, 0, GetColorF(0.5f, 0.3f, 1.0f, 1.0f));
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
Field::~Field()
{
	MV1DeleteModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  ��������.
//-----------------------------------------------------------------------------
void Field::CreateInstance()
{
	if (m_field == nullptr)
	{
		m_field = new Field;
	}
}

//-----------------------------------------------------------------------------
// @brief  �������.
//-----------------------------------------------------------------------------
void Field::DeleteInstance()
{
	if (m_field != nullptr)
	{
		delete m_field;
		m_field = nullptr;
	}
}

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void Field::Update()
{
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void Field::Draw()
{
	// �n�ʂ̃^�C���`��
	{
		// 0 1 2
		// 3 4 5
		// 6 7 8
		// ��L�ʂ�`�悵����

		// 0
		MV1SetPosition(m_modelHandle, VGet(-775.0f, 0.0f, 600.0f));
		MV1DrawModel(m_modelHandle);

		// 1
		MV1SetPosition(m_modelHandle, VGet(0.0f, 0.0f, 600.0f));
		MV1DrawModel(m_modelHandle);

		// 2
		MV1SetPosition(m_modelHandle, VGet(775.0f, 0.0f, 600.0f));
		MV1DrawModel(m_modelHandle);

		// 3
		MV1SetPosition(m_modelHandle, VGet(-775.0f, 0.0f, 0.0f));
		MV1DrawModel(m_modelHandle);

		// 4
		MV1SetPosition(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
		MV1DrawModel(m_modelHandle);

		// 5
		MV1SetPosition(m_modelHandle, VGet(775.0f, 0.0f, 0.0f));
		MV1DrawModel(m_modelHandle);

		// 6
		MV1SetPosition(m_modelHandle, VGet(-775.0f, 0.0f, -600.0f));
		MV1DrawModel(m_modelHandle);

		// 7
		MV1SetPosition(m_modelHandle, VGet(0.0f, 0.0f, -600.0f));
		MV1DrawModel(m_modelHandle);

		// 8
		MV1SetPosition(m_modelHandle, VGet(775.0f, 0.0f, -600.0f));
		MV1DrawModel(m_modelHandle);
	}
}

//-----------------------------------------------------------------------------
// @brief  �X�V�����Ăїp�֐�.
//-----------------------------------------------------------------------------
void Field::UpdateCall()
{
	m_field->Update();
}

//-----------------------------------------------------------------------------
// @brief  �`�揈���Ăїp�֐�.
//-----------------------------------------------------------------------------
void Field::DrawCall()
{
	m_field->Draw();
}