//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	void Init();			// 初期化処理.
	void Update() override;	// 更新処理.
	void Draw() override;	// 描画処理.
	void Input();			// 入力処理.
	void Rotate();			// 回転処理.
	void Animation();		// アニメーション処理.
	void Move() override;	// 行動処理.
	void LevelManager();	// レベルとステータス管理処理.

	void SetUseSkill(SKILL _skillCommand)
	{
		m_useSkill = _skillCommand;
	}

	void EXPAdd(int exp)	// 経験値取得＋レベルアップ処理呼び
	{
		int EXP = m_status.EXP;
		EXP = EXP + exp;
		if (EXP >= m_expMAX)
		{
			m_status.EXP = EXP;
			EXP = EXP - m_expMAX;
			LevelManager();
			m_status.EXP = EXP;
		}
		else
		{
			m_status.EXP = EXP;
		}
	}

	// ゲッター
	const int& GetMPMAX() { return m_mpMAX; }
	const int& GetEXPMAX() { return m_expMAX; }
	const SKILL* GetSKILL() { return m_skillStorage; }
private:
	void Camera();
	// 二つのベクトルの角度が同じか.
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVecからdirVecの最短の回転方向を調べる(Y軸).
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する.
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	int m_mpMAX;			// プレイヤーの最大魔法力量.
	int m_expMAX;			// プレイヤーのレベルアップに必要な経験値量.

	bool m_rotateNow;		// 回転中か判定用.

	VECTOR m_rotate;		// プレイヤーの角度.
	VECTOR m_velocity;		// プレイヤーの速度.
	VECTOR m_dir;			// プレイヤーの向き.
	VECTOR m_aimDir;		// プレイヤーの目標方向.
};