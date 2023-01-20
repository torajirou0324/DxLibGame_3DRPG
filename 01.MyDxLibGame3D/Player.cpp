//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------
#include "Player.h"
#include <math.h>
#include "Input.h"

Player* Player::m_player = nullptr;
const float r = -60.0f;					// プレイヤーとカメラの距離

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Player::Player()
	: m_position(VGet(0, 0, 0))
	, m_rotate(VGet(0.0f,0.0f,0.0f))
	, m_velocity(VGet(0.0f,0.0f,0.0f))
	, m_dir(VGet(0, 0, 1))
	, m_aimDir(VGet(0, 0, 0))
	, m_cameraPosition(VGet(0.0f, 0.0f, 0.0f))
	, m_cameraViewPoint(VGet(0.0f,0.0f,0.0f))
	, m_rotateNow(false)
	, m_battleFlag(true)
	, m_animTime(0.0f)
	, m_animTotalTime(0.0f)
	, m_animType(Idle)
	, m_beforeAnimType(Idle)
{
	// モデルにテクスチャをセット
	m_modelHandle = (MV1LoadModel("data/player/Player.mv1"));
	int GraphHandle = LoadGraph("data/player/playertex.png");
	int GraphHandle1 = LoadGraph("data/player/playertex1.png");
	int GraphHandle2 = LoadGraph("data/player/playertex2.png");
	int GraphHandle3 = LoadGraph("data/player/playertex3.png");
	MV1SetTextureGraphHandle(m_modelHandle, 0, GraphHandle, TRUE);
	MV1SetTextureGraphHandle(m_modelHandle, 1, GraphHandle2, TRUE);
	MV1SetTextureGraphHandle(m_modelHandle, 2, GraphHandle, TRUE);
	MV1SetTextureGraphHandle(m_modelHandle, 3, GraphHandle2, TRUE);
	MV1SetTextureGraphHandle(m_modelHandle, 4, GraphHandle, TRUE);
	MV1SetTextureGraphHandle(m_modelHandle, 5, GraphHandle1, TRUE);

	// モデルの大きさをセット
	MV1SetScale(m_modelHandle, VGet(0.2f, 0.2f, 0.2f));
	
	// アニメーションを保存
	m_animHandle[0] = MV1LoadModel("data/player/animIdle.mv1");
	m_animHandle[1] = MV1LoadModel("data/player/animWalk.mv1");
	m_animHandle[2] = MV1LoadModel("data/player/animAttack.mv1");
	m_animHandle[3] = MV1LoadModel("data/player/animDamage.mv1");
	m_animHandle[4] = MV1LoadModel("data/player/animDeath.mv1");

	// アニメーションの初期化
	MV1DetachAnim(m_modelHandle, 0);
	auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
	m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
	m_animTime = 0.0f;
	m_beforeAnimType = m_animType;

	// ステータスの初期化
	m_playerStatus.LV = 1;
	m_playerStatus.HP = 12;
	m_playerStatus.ATK = 6;
	m_playerStatus.AGL = 6;
	m_playerStatus.EXP = 0;
	m_hpMAX = m_playerStatus.HP;
	m_expMAX = 2;
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Player::~Player()
{
	// プレイヤーを削除.
	MV1DeleteModel(m_modelHandle);
	// アニメーションを削除
	for (int i = 0; i < 5; i++)
	{
		MV1DeleteModel(m_animHandle[i]);
	}
}

//-----------------------------------------------------------------------------
// @brief  生成処理.
//-----------------------------------------------------------------------------
void Player::CreateInstance()
{
	if (m_player == nullptr)
	{
		m_player = new Player;
	}
}

//-----------------------------------------------------------------------------
// @brief  解放処理.
//-----------------------------------------------------------------------------
void Player::DeleteInstance()
{
	if (m_player != nullptr)
	{
		delete m_player;
		m_player = nullptr;
	}
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void Player::Init()
{
	auto vec = VGet(0, 0, 0);
	m_position = vec;
	m_rotate = vec;
	m_velocity = vec;
	m_dir = VGet(0, 0, 1);
	m_aimDir = vec;
	m_cameraViewPoint = vec;
	m_rotateNow = false;
	m_battleFlag = true;
	m_animType = Idle;
	m_beforeAnimType = Idle;
	m_animTime = 0.0f;
	m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], 0);
}

void Player::InitCall()
{
	m_player->Init();
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void Player::Update()
{
	m_player->Rotate();			// 回転
	m_player->Animation();		// アニメーション
	m_player->Input();			// 入力
	m_player->Camera();			// 追従カメラ
	m_player->LevelManager();	// レベルとステータス管理処理

	m_player->m_position = VAdd(m_player->m_position, m_player->m_velocity);

	// 向きに合わせてモデル回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_player->m_dir, rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_player->m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// ３Dモデルのポジション設定
	MV1SetPosition(m_player->m_modelHandle, m_player->m_position);
}

void Player::DrawCall()
{
	m_player->Draw();
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void Player::Draw()
{
	//printfDx("posX:%3f posY:%3f posZ:%3f\n", m_position.x, m_position.y, m_position.z);
	// プレイヤー描画.
	MV1DrawModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  ボタンの入力処理.
//-----------------------------------------------------------------------------
void Player::Input()
{
	if (m_battleFlag) 
	{ 
		m_velocity = VGet(0.0f, 0.0f, 0.0f);
		// 戦闘中のため歩くモーションは停止
		if (m_animType == Walk)
		{
			m_animType = Idle;
		}
		return;
	}

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
		//m_position.z += 1;
	}

	// 下を押していたら下に進む
	if (Input::IsPressed(DOWN) || inputState.ThumbLY < -2000.0f)
	{
		back.x = sinf(m_rotate.y) * -1.0f;
		back.z = cosf(m_rotate.y) * -1.0f;
		inputVector = VAdd(back, inputVector);
		input = true;
		//m_position.z -= 1;
	}

	// 右を押していたら右に進む
	if (Input::IsPressed(RIGHT) || inputState.ThumbLX > 2000.0f)
	{
		right.x = sinf(m_rotate.y + addRad);
		right.z = cosf(m_rotate.y + addRad);
		inputVector = VAdd(right, inputVector);
		input = true;
		m_rotate.y += 0.02f;
		//m_position.x += 1;
	}

	// 左を押していたら左に進む
	if (Input::IsPressed(LEFT) || inputState.ThumbLX < -2000.0f)
	{
		left.x = sinf(m_rotate.y - addRad);
		left.z = cosf(m_rotate.y - addRad);
		inputVector = VAdd(left, inputVector);
		input = true;
		m_rotate.y -= 0.02f;
		//m_position.x -= 1;
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
		//auto posX = m_position.x + sinf(m_rotate.y) * -30;
		//auto posZ = m_position.z + cosf(m_rotate.y) * -30;
		//auto aimPos = VGet(posX, 0.0f, posZ);
		//aimPos = VSub(m_position, aimPos);
		//VScale(aimPos, -1);
		//aimPos = VNorm(aimPos);

		//m_dir = aimPos;
		//m_aimDir = aimPos;

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

void Player::Camera()
{
	m_cameraViewPoint = m_position;

	m_cameraPosition.x = m_cameraViewPoint.x + sinf(m_rotate.y) * r;
	m_cameraPosition.z = m_cameraViewPoint.z + cosf(m_rotate.y) * r;

	// カメラの注視点をセット
	m_cameraViewPoint.y = m_cameraViewPoint.y + 15.0f;
	m_cameraPosition.y = m_cameraViewPoint.y + 20.0f;

	SetCameraPositionAndTarget_UpVecY(m_cameraPosition, m_cameraViewPoint);
}

void Player::LevelManager()
{
	if (m_playerStatus.EXP >= m_expMAX)
	{
		m_playerStatus.EXP = 0;
		auto addMaxEXP = m_expMAX / 2;
		m_expMAX = m_expMAX + addMaxEXP;
		m_playerStatus.LV++;
		m_playerStatus.HP = 2 + m_hpMAX;
		m_playerStatus.ATK++;
		m_playerStatus.AGL++;
		m_hpMAX += 2;
	}
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
