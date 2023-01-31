//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------
#pragma once
#include "Character.h"

class Player : public Character
{
private:
	static Player* m_player;

	int m_expMAX;			// プレイヤーのレベルアップに必要な経験値量.
	int m_animHandle[5];	// アニメーションのモデルハンドル.

	bool m_rotateNow;		// 回転中か判定用.

	VECTOR m_rotate;		// プレイヤーの角度.
	VECTOR m_velocity;		// プレイヤーの速度.
	VECTOR m_dir;			// プレイヤーの向き.
	VECTOR m_aimDir;		// プレイヤーの目標方向.

	VECTOR m_cameraPosition;// カメラの位置座標.
	VECTOR m_cameraViewPoint;	// 追従カメラ注視座標.

	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	void Init();			// 初期化処理.
	void Update();			// 更新処理.
	void Draw();			// 描画処理.
	void Input();			// 入力処理.
	void Rotate();			// 回転処理.
	void Animation();		// アニメーション処理.
	void Camera();			// 追従カメラ更新処理.

	// 二つのベクトルの角度が同じか.
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVecからdirVecの最短の回転方向を調べる(Y軸).
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する.
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);
public:
	Player(const Player&) = delete;				// コピーコンストラクタをdelete指定.
	Player& operator=(const Player&) = delete;	// コピー代入演算子もdelete指定.
	Player(Player&&) = delete;					// ムーブコンストラクタをdelete指定.
	Player& operator=(Player&&) = delete;		// ムーブ代入演算子もdelete指定.

	static void CreateInstance();				// 生成処理.
	static void DeleteInstance();				// 解放処理.

	static void InitCall();		// 初期化処理呼び用関数.
	static void UpdateCall();	// 更新処理呼び用関数.
	static void DrawCall();		// 描画処理呼び用関数.
	static void LevelManager();	// レベルとステータス管理処理.

	static void Damage(int atk)	// 被ダメ処理
	{
		int HP = m_player->m_status.HP;
		HP = HP - atk;
		if (HP < 0)
		{
			HP = 0;
		}
		m_player->m_status.HP = HP;
	}

	// セッター
	static void SetAnimType(const Anim& _animType) { m_player->m_animType = _animType; }
	// ゲッター
	static const int& GetHPMAX() { return m_player->m_hpMax; }
	static const int& GetEXPMAX() { return m_player->m_expMAX; }
	static const Status& GetAllStatus() { return m_player->m_status; }
	static Player* GetAddress() { return m_player->m_player; }
};