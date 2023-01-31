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

	VECTOR m_rotate;		// プレイヤーの角度.
	VECTOR m_velocity;		// プレイヤーの速度.
	VECTOR m_dir;			// プレイヤーの向き.
	VECTOR m_aimDir;		// プレイヤーの目標方向.

	VECTOR m_cameraPosition;// カメラの位置座標.
	VECTOR m_cameraViewPoint;	// 追従カメラ注視座標.

	bool m_rotateNow;		// 回転中か判定用.
	bool m_battleFlag;		// 戦闘中か判定用.

	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	void Init();			// 初期化処理.
	void Draw();
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

	static void CreateInstance();
	static void DeleteInstance();

	static void InitCall();		// 初期化処理呼び用関数.
	static void Update();		// 更新処理.
	static void DrawCall();		// 描画処理.
	static void LevelManager();	// レベルとステータス管理処理.

	// セッター
	static void SetBattleFlag(const bool& _flag) { m_player->m_battleFlag = _flag; }
	static void SetAnimType(const Anim& _animType) { m_player->m_animType = _animType; }
	static void SetAllStatus(const Status& _status) { m_player->m_status = _status; }
	// ゲッター
	static const int& GetHPMAX() { return m_player->m_hpMax; }
	static const int& GetEXPMAX() { return m_player->m_expMAX; }
	static const bool& GetBattleFlag() { return m_player->m_battleFlag; }
	static const float& GetAnimTime() { return m_player->m_animTime; }
	static const float& GetAnimTotalTime() { return m_player->m_animTotalTime; }
	static const VECTOR& GetPlayerPosition() { return m_player->m_position; }
	static const VECTOR& GetDir() { return m_player->m_dir; }
	static const Anim& GetAnimType() { return m_player->m_animType; }
	static const Status& GetAllStatus() { return m_player->m_status; }
};