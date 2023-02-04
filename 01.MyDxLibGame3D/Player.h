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
	void Update();			// 更新処理.
	void Draw();			// 描画処理.
	void Input();			// 入力処理.
	void Rotate();			// 回転処理.
	void Animation();		// アニメーション処理.
	void LevelManager();	// レベルとステータス管理処理.

	void HPHeal()
	{
		int HP = m_status.HP;
		HP = HP + (3 * m_status.LV);
		if (m_hpMax < HP)
		{
			HP = m_hpMax;
		}
		m_status.HP = HP;
		Action();
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

	// セッター
	void SetAnimType(const Anim& _animType) { m_animType = _animType; }
	// ゲッター
	const int& GetEXPMAX() { return m_expMAX; }
private:
	int m_expMAX;			// プレイヤーのレベルアップに必要な経験値量.

	bool m_rotateNow;		// 回転中か判定用.

	VECTOR m_rotate;		// プレイヤーの角度.
	VECTOR m_velocity;		// プレイヤーの速度.
	VECTOR m_dir;			// プレイヤーの向き.
	VECTOR m_aimDir;		// プレイヤーの目標方向.

	VECTOR m_cameraPosition;// カメラの位置座標.
	VECTOR m_cameraViewPoint;	// 追従カメラ注視座標.

	// 二つのベクトルの角度が同じか.
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVecからdirVecの最短の回転方向を調べる(Y軸).
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する.
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

};