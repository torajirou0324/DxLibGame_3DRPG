//-----------------------------------------------------------------------------
// @brief  �t�B�[���h�ɕ~���n�ʕ`��p�ÓI�N���X.
//-----------------------------------------------------------------------------
#include "Field.h"
#include <DxLib.h>
#include "AssetManager.h"

Field* Field::m_field = nullptr;

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Field::Field()
{
	m_fieldHandle = AssetManager::UseModel(AssetManager::Field);
	m_wallHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::Field));
	m_blackBox = MV1DuplicateModel(AssetManager::UseModel(AssetManager::Field));
	int GraphHandle = AssetManager::UseImage(AssetManager::MapTile);
	MV1SetTextureGraphHandle(m_fieldHandle, 0, GraphHandle, TRUE);
	MV1SetTextureGraphHandle(m_wallHandle, 0, GraphHandle, TRUE);
	MV1SetScale(m_fieldHandle, VGet(100.0f, 1.0f, 100.0f));
	MV1SetScale(m_wallHandle, VGet(100.0f, 100.0f, 100.0f));
	MV1SetScale(m_blackBox, VGet(100.0f, 100.0f, 100.0f));
	MV1SetMaterialDifColor(m_blackBox, 0, GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
Field::~Field()
{
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

		// �^�񒆂̑O�����̕�
		MV1SetPosition(m_wallHandle, VGet(100.0f, 50.0f, 300.0f));
		MV1DrawModel(m_wallHandle);
		MV1SetPosition(m_wallHandle, VGet(-100.0f, 50.0f, 300.0f));
		MV1DrawModel(m_wallHandle);
		MV1SetPosition(m_blackBox, VGet(0.0f, 50.0f, 300.0f));
		MV1DrawModel(m_blackBox);

		// �^�񒆂̑O�������E�̕�
		MV1SetPosition(m_wallHandle, VGet(100.0f, 50.0f, 200.0f));
		MV1DrawModel(m_wallHandle);
		MV1SetPosition(m_wallHandle, VGet(-100.0f, 50.0f, 200.0f));
		MV1DrawModel(m_wallHandle);

		// �^�񒆂̑O�����̏�
		MV1SetPosition(m_fieldHandle, VGet(0.0f, 0.0f, 200.0f));
		MV1DrawModel(m_fieldHandle);
		MV1SetPosition(m_fieldHandle, VGet(0.0f, 0.0f, 100.0f));
		MV1DrawModel(m_fieldHandle);

		// �O�������̕�
		MV1SetPosition(m_wallHandle, VGet(-100.0f, 50.0f, 100.0f));
		MV1DrawModel(m_wallHandle);
		MV1SetPosition(m_wallHandle, VGet(-100.0f, 50.0f, 0.0f));
		MV1DrawModel(m_wallHandle);

		// �O�����E�̕�
		MV1SetPosition(m_wallHandle, VGet(100.0f, 50.0f, 100.0f));
		MV1DrawModel(m_wallHandle);
		MV1SetPosition(m_wallHandle, VGet(100.0f, 50.0f, 0.0f));
		MV1DrawModel(m_wallHandle);

		// �^�񒆂̏� 4
		MV1SetPosition(m_fieldHandle, VGet(0.0f, 0.0f, 0.0f));
		MV1DrawModel(m_fieldHandle);

		// �^�񒆌��̕� 7
		MV1SetPosition(m_wallHandle, VGet(0.0f, 50.0f, -100.0f));
		MV1DrawModel(m_wallHandle);
	}
}

void Field::BattleUpdate()
{
}

void Field::BattleDraw()
{
	for (int vertical = 0; vertical < 3; vertical++)
	{
		for (int side = 0; side < 3; side++)
		{
			VECTOR position = VGet(100.0f * (side - 1) , 0.0f, 100.0f * (1 - vertical));
			MV1SetPosition(m_fieldHandle, position);
			MV1DrawModel(m_fieldHandle);
		}
	}

	for (int vertical = 0; vertical < 3; vertical++)
	{
		MV1SetPosition(m_wallHandle, VGet(-100.0f * (vertical -1), 50.0f, 200.0f));
		MV1DrawModel(m_wallHandle);
	}

	MV1SetPosition(m_wallHandle, VGet(-200.0f, 50.0f, 100.0f));
	MV1DrawModel(m_wallHandle);
	MV1SetPosition(m_wallHandle, VGet(200.0f, 50.0f, 100.0f));
	MV1DrawModel(m_wallHandle);
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

void Field::BattleUpdateCall()
{
}

void Field::BattleDrawCall()
{
	m_field->BattleDraw();
}
