//-----------------------------------------------------------------------------
// @brief  フィールドに敷く地面描画用静的クラス.
//-----------------------------------------------------------------------------
#pragma once

class Field
{
private:
	static Field* m_field;
	int m_fieldHandle;
	int m_wallHandle;
	int m_blackBox;

	Field();
	~Field();

	void Update();	// 更新処理.
	void Draw();	// 描画処理.
public:
	Field(const Field&) = delete;				// コピーコンストラクタを delete 指定.
	Field& operator=(const Field&) = delete;	// コピー代入演算子も delete 指定.
	Field(Field&&) = delete;					// ムーブコンストラクタを delete 指定.
	Field& operator=(Field&&) = delete;			// ムーブ代入演算子も delete 指定.

	static void CreateInstance();	// 生成処理.
	static void DeleteInstance();	// 解放処理.

	static void UpdateCall();		// 更新処理呼び用関数.
	static void DrawCall();			// 描画処理呼び用関数.
};