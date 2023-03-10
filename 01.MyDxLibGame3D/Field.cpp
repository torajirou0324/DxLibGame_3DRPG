//-----------------------------------------------------------------------------
// @brief  フィールドに敷く地面描画用静的クラス.
//-----------------------------------------------------------------------------
#include "Field.h"

#include <DxLib.h>
#include "AssetManager.h"
#include "ColliderManager.h"
#include "WallCollider.h"

Field* Field::m_field = nullptr;

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Field::Field()
{
	m_fieldHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::Field));
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
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Field::~Field()
{
	MV1DeleteModel(m_fieldHandle);
	MV1DeleteModel(m_wallHandle);
	MV1DeleteModel(m_blackBox);
}

//-----------------------------------------------------------------------------
// @brief  生成処理.
//-----------------------------------------------------------------------------
void Field::CreateInstance()
{
	if (m_field == nullptr)
	{
		m_field = new Field;
	}
}

//-----------------------------------------------------------------------------
// @brief  解放処理.
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
// @brief  更新処理.
//-----------------------------------------------------------------------------
void Field::Update()
{
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void Field::Draw()
{
	// 地面のタイル描画
	{
		for (int vertical = 0; vertical < 3; vertical++)
		{
			for (int side = 0; side < 3; side++)
			{
				VECTOR position = VGet(100.0f * (side - 1), 0.0f, 100.0f * (1 - vertical));
				MV1SetPosition(m_fieldHandle, position);
				MV1DrawModel(m_fieldHandle);
			}
		}

		for (int side = 0; side < 3; side++)
		{
			VECTOR position = VGet(0.0f, 0.0f, 400.0f - (100.0f * side));
			MV1SetPosition(m_fieldHandle, position);
			MV1DrawModel(m_fieldHandle);
			position = VGet(-100.0f, 50.0f, 400.0f - (100.0f * side));
			MV1SetPosition(m_wallHandle, position);
			MV1DrawModel(m_wallHandle);
			position = VGet(100.0f, 50.0f, 400.0f - (100.0f * side));
			MV1SetPosition(m_wallHandle, position);
			MV1DrawModel(m_wallHandle);
		}

		for (int vertical = 0; vertical < 3; vertical++)
		{
			for (int side = 0; side < 3; side++)
			{
				VECTOR position = VGet(100.0f * (side - 1), 0.0f, 700.0f - (100.0f * vertical));
				MV1SetPosition(m_fieldHandle, position);
				MV1DrawModel(m_fieldHandle);
			}
		}
	}

	for (int vertical = 0; vertical < 4; vertical++)
	{
		// 左の壁
		VECTOR position = VGet(-200.0f, 50.0f, -100.0f * (vertical - 1));
		MV1SetPosition(m_wallHandle, position);
		MV1DrawModel(m_wallHandle);
		// 右の壁
		position = VGet(200.0f, 50.0f, 100.0f * (vertical - 1));
		MV1SetPosition(m_wallHandle, position);
		MV1DrawModel(m_wallHandle);
		// 後の壁
		position = VGet(100.0f * (vertical - 1), 50.0f, -200.0f);
		MV1SetPosition(m_wallHandle, position);
		MV1DrawModel(m_wallHandle);
	}

	// 壁
	for (int side = 0; side < 5; side++)
	{
		VECTOR position = VGet(-200.0f + (side * 100.0f), 50.0f, 800.0f);
		MV1SetPosition(m_wallHandle, position);
		MV1DrawModel(m_wallHandle);

		position = VGet(-200.0f, 50.0f, 800.0f - (side * 100.0f));
		MV1SetPosition(m_wallHandle, position);
		MV1DrawModel(m_wallHandle);

		position = VGet(200.0f, 50.0f, 800.0f - (side * 100.0f));
		MV1SetPosition(m_wallHandle, position);
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
// @brief  更新処理呼び用関数.
//-----------------------------------------------------------------------------
void Field::UpdateCall()
{
	m_field->Update();
}

//-----------------------------------------------------------------------------
// @brief  描画処理呼び用関数.
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
