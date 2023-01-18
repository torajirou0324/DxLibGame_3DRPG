//-----------------------------------------------------------------------------
// @brief  フィールドに敷く地面描画用静的クラス.
//-----------------------------------------------------------------------------
#include "Field.h"
#include <DxLib.h>

Field* Field::m_field = nullptr;

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
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
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Field::~Field()
{
	MV1DeleteModel(m_modelHandle);
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
		// 0 1 2
		// 3 4 5
		// 6 7 8
		// 上記通り描画したい

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