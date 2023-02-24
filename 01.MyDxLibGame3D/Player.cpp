//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------
#include "Player.h"
#include <math.h>
#include "Input.h"

const float r = -80.0f;					// プレイヤーとカメラの距離
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Player::Player()
	: m_rotate(VGet(0.0f,0.0f,0.0f))
	, m_velocity(VGet(0.0f,0.0f,0.0f))
	, m_dir(VGet(0, 0, 1))
	, m_aimDir(VGet(0, 0, 0))
	, m_rotateNow(false)
{
	// プレイヤーです
	m_isPlayerFlag = true;

	// モデルをロード
	m_modelHandle = AssetManager::UseModel(AssetManager::Player);

	// アニメーションの初期化
	MV1DetachAnim(m_modelHandle, 0);
	auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
	m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
	m_animTime = 0.0f;
	m_beforeAnimType = m_animType;
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Player::~Player()
{
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void Player::Init()
{
	m_name = "キツキ　イチカ";

	// ステータスの初期化
	m_status.LV = 1;
	m_status.HP = 18;
	m_status.MP = 3;
	m_status.ATK = 5;
	m_status.DEF = 5;
	m_status.INT = 5;
	m_status.RES = 5;
	m_status.AGL = 5;
	m_status.EXP = 0;
	m_hpMax = m_status.HP;
	m_mpMAX = m_status.MP;
	m_expMAX = 1;

	auto vec = VGet(0, 0, 0);
	m_position = vec;
	m_rotate = vec;
	m_velocity = vec;
	m_dir = VGet(0, 0, 1);
	m_aimDir = vec;
	m_rotateNow = false;
	m_animType = Idle;
	m_beforeAnimType = Idle;
	m_animTime = 0.0f;
	m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], 0);

	// 技のスキルの世界
	SKILL skillarray[4] = {
		{"たたく", AttributeType::Physical, 10,0,0},
		{"フレア",AttributeType::Special,20,3,0},
		{"ヒール",AttributeType::Recovery,10,2,0},
		{"",AttributeType::None,0,0,0}
	};

	for (int i = 0; i < 4; i++)
	{
		m_skillStorage[i] = skillarray[i];
	}
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void Player::Update()
{
	Rotate();			// 回転
	Animation();		// アニメーション
	Input();			// 入力
	Camera();

	m_position = VAdd(m_position, m_velocity);

	// 向きに合わせてモデル回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_position);
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void Player::Draw()
{
	printfDx("posX:%3f posY:%3f posZ:%3f\n", m_position.x, m_position.y, m_position.z);
	printfDx("%3f", m_animTime);
	// プレイヤー描画.
	MV1DrawModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  ボタンの入力処理.
//-----------------------------------------------------------------------------
void Player::Input()
{
	VECTOR inputVector = { 0.0f,0.0f,0.0f }; // 押した合計座標取得用関数

	// 前後左右
	VECTOR front = { 0.0f,0.0f,1.0f };
	VECTOR back  = { 0.0f,0.0f,-1.0f };
	VECTOR left  = { 1.0f,0.0f,0.0f };
	VECTOR right = { -1.0f,0.0f,0.0f };

	float addRad = 1.58f;	// 加算する角度
	bool input = false;		// 入力したか判定用

	XINPUT_STATE inputState;

	// 入力状態を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

	// 上を押していたら上に進む
	if (Input::IsPressed(UP) || inputState.ThumbLY > 2000.0f)
	{
		front.x = sinf(m_rotate.y);
		front.z = cosf(m_rotate.y);
		inputVector = VAdd(front, inputVector);
		input = true;
	}

	// 下を押していたら下に進む
	if (Input::IsPressed(DOWN) || inputState.ThumbLY < -2000.0f)
	{
		back.x = sinf(m_rotate.y) * -1.0f;
		back.z = cosf(m_rotate.y) * -1.0f;
		inputVector = VAdd(back, inputVector);
		input = true;
	}

	// 右を押していたら右に進む
	if (Input::IsPressed(RIGHT) || inputState.ThumbLX > 2000.0f)
	{
		right.x = sinf(m_rotate.y + addRad);
		right.z = cosf(m_rotate.y + addRad);
		inputVector = VAdd(right, inputVector);
		input = true;
		m_rotate.y += 0.02f;
	}

	// 左を押していたら左に進む
	if (Input::IsPressed(LEFT) || inputState.ThumbLX < -2000.0f)
	{
		left.x = sinf(m_rotate.y - addRad);
		left.z = cosf(m_rotate.y - addRad);
		inputVector = VAdd(left, inputVector);
		input = true;
		m_rotate.y -= 0.02f;
	}

	// 入力有（加速）・入力無（減速）
	if (input)
	{
		m_animType = Walk;
		// 左右・前後同時押しなどで入力ベクトルが0の時は無視
		if (VSquareSize(inputVector) < 0.5f)
		{
			return;
		}

		// 方向を正規化
		inputVector = VNorm(inputVector);

		// 入力方向は現在向いている向きと異なるか
		if (IsNearAngle(inputVector, m_dir))
		{
			m_dir = inputVector;
		}
		else
		{
			m_rotateNow = true;
			m_aimDir = inputVector;
		}
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.99f;
		m_velocity.z = m_velocity.z * 0.99f;

		if (m_velocity.x < 0.1)
		{
			m_animType = Idle;
		}
	}

	m_velocity = inputVector;
}

//-----------------------------------------------------------------------------
// @brief  回転処理.
//-----------------------------------------------------------------------------
void Player::Rotate()
{
	if (m_rotateNow)
	{
		// 回転が目標角度に到達すれば回転モード終了
		if (IsNearAngle(m_aimDir, m_dir))
		{
			m_dir = m_aimDir;
			m_rotateNow = false;
		}
		else
		{
			// 回転
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(m_dir, m_aimDir, 10.0f);

			// 回転が目標角度を超えていないか
			VECTOR cross1, cross2;
			cross1 = VCross(m_dir, m_aimDir);
			cross2 = VCross(interPolateDir, m_aimDir);

			// 目標角度を超えたら終了
			if (cross1.y * cross2.y < 0.0f)
			{
				interPolateDir = m_aimDir;
				m_rotateNow = false;
			}
			// 目標ベクトルに10度だけ近づえた角度
			m_dir = interPolateDir;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  アニメーション処理.
//-----------------------------------------------------------------------------
void Player::Animation()
{
	// アニメーション繰り返し処理
	if (m_animTotalTime < m_animTime)
	{
		m_animTime = 0.0f;
		if (m_animType == Anim::Death)
		{
			m_isDeathFlag = true;
			m_animTime = m_animTotalTime;
		}
		m_animType = Anim::Idle;
		m_attackNow = false;
	}

	// アニメーション切り替え処理
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_modelHandle, 0);
		auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
		m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}

	// 現在のアニメーションフレームをモデルにアタッチする
	MV1SetAttachAnimTime(m_modelHandle, 0, m_animTime);

	// アニメーションフレーム加算
	m_animTime += 0.3f;
}

void Player::Move()
{
	Action();

	if (m_useSkill.SkillType == AttributeType::Recovery)
	{
		Heal();
		return;
	}

	Attack();
}

//-----------------------------------------------------------------------------
// @brief  レベル＋ステータス管理処理.
//-----------------------------------------------------------------------------
void Player::LevelManager()
{
	if (m_status.EXP >= m_expMAX)
	{
		m_status.LV++;
		m_status.EXP = 0;
		m_hpMax += 3;
		m_status.HP = m_hpMax;
		m_mpMAX += 3;
		m_status.MP = m_mpMAX;
		m_expMAX += 3;
		m_status.ATK += 2;
		m_status.DEF++;
		m_status.INT += 2;
		m_status.RES++;
		m_status.AGL += 2;
	}
}

void Player::Camera()
{
	VECTOR cameraPos = VGet(0.0f, 180.0f, 0.0f);

	cameraPos.x = m_position.x + sinf(m_rotate.y) * r;
	cameraPos.z = m_position.z + cosf(m_rotate.y) * r;

	SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(m_position.x,m_position.y + 40,m_position.z));
}

//-----------------------------------------------------------------------------
// @brief  二つのベクトルの角度が同じか.
//-----------------------------------------------------------------------------
bool Player::IsNearAngle(const VECTOR& v1, const VECTOR& v2)
{
	float dot = VDot(v1, v2);
	if (dot < 0.99f)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// @brief  nowVecからdirVecの最短の回転方向を調べる(Y軸).
//-----------------------------------------------------------------------------
float Player::CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
{
	VECTOR axis;
	axis = VCross(nowVec, dirVec);
	if (axis.y < 0.0f)
	{
		return -1.0f;
	}
	return 1.0f;
}

//-----------------------------------------------------------------------------
// @brief  nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する.
//-----------------------------------------------------------------------------
VECTOR Player::RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
{
	// 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
	float rotRadian = (DX_PI_F * degreeVelocity / 180.0f);
	rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

	// Y軸回転行列を作成する
	MATRIX yRotMat = MGetRotY(rotRadian);

	// Y軸回転する
	VECTOR rotVec;
	rotVec = VTransform(nowVec, yRotMat);
	return rotVec;
}
