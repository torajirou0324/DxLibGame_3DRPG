//-----------------------------------------------------------------------------
// @brief  マップを徘徊する敵クラス.
//-----------------------------------------------------------------------------
#include "WalkAroundEnemy.h"

#include "ColliderManager.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
WalkAroundEnemy::WalkAroundEnemy()
    : m_iconHandle(-1)
    , m_level(0)
    , m_num(0)
    , m_timer(0)
    , m_animTime(0.0f)
    , m_animTotalTime(0.0f)
    , m_rotateNow(false)
    , m_isCollisionPlayer(false)
    , m_position(VGet(0.0f, 0.0f, 0.0f))
    , m_rotate(VGet(0.0f, 0.0f, 0.0f))
    , m_velocity(VGet(0.0f, 0.0f, 0.0f))
    , m_dir(VGet(0.0f, 0.0f, 0.0f))
    , m_aimDir(VGet(0.0f, 0.0f, 0.0f))
    , m_pBoxCollider(nullptr)
    , m_animType(Anim::Idle)
    , m_beforeAnimType(Anim::Idle)
{
    // モデルをロード
    m_modelHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::Deamon));
    // 向きに合わせてモデル回転

    // ３Dモデルのポジション設定
    MV1SetPosition(m_modelHandle, m_position);
    // モデルの大きさをセット
    MV1SetScale(m_modelHandle, VGet(0.2f, 0.20f, 0.2f));

    int GraphHandle1 = AssetManager::UseImage(AssetManager::DeamonTexture1);
    int GraphHandle2 = AssetManager::UseImage(AssetManager::DeamonTexture2);
    int GraphHandle3 = AssetManager::UseImage(AssetManager::DeamonTexture3);
    MV1SetTextureGraphHandle(m_modelHandle, 0, GraphHandle1, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 1, GraphHandle2, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 2, GraphHandle3, TRUE);

    // アニメーションを保存
    m_animHandle[0] = AssetManager::UseModel(AssetManager::AnimIdle);
    m_animHandle[1] = AssetManager::UseModel(AssetManager::AnimWalk);
    m_animHandle[2] = AssetManager::UseModel(AssetManager::AnimAttack);
    m_animHandle[3] = AssetManager::UseModel(AssetManager::AnimDamage);
    m_animHandle[4] = AssetManager::UseModel(AssetManager::AnimDeath);

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
WalkAroundEnemy::~WalkAroundEnemy()
{
	MV1DeleteModel(m_modelHandle);
    if (m_pBoxCollider != nullptr)
    {
        delete m_pBoxCollider;
    }
}

//-----------------------------------------------------------------------------
// @brief  初期化処理.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Init(const VECTOR& _pos, int _ownLevel, int _otherLevel)
{
    m_level = _ownLevel;
    m_velocity = VGet(1.0f, 0.0f, -1.0f);

    // ポジションをセット
    m_position = _pos;
    // 向き方向
    m_dir = VGet(0.0f, 0.0f, -1.0f);
    // 敵の数を乱数でセット
    m_num = GetRand(2) + 1;

    // コライダーをセット
    m_pBoxCollider = new BoxCollider;
    m_pBoxCollider->Init(m_position, VGet(20.0f, 50.0f, 20.0f), ObjectTag::Enemy, std::bind(&WalkAroundEnemy::PushbackVolume, this));
    ColliderManager::AddColliderInfo(m_pBoxCollider);

    // プレイヤーとのレベル比較して視覚的に強いかどうかを知らせるためにアイコンをセット
    if (m_level == _otherLevel)
    {
        m_iconHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::IconGreen));
        return;
    }
    if (m_level < _otherLevel)
    {
        m_iconHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::IconBlue));
        return;
    }
    if (m_level > _otherLevel)
    {
        m_iconHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::IconRed));
        return;
    }
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Update()
{
    Move();             // 移動
    Rotate();			// 回転
    Animation();		// アニメーション

    m_position = VAdd(m_position, m_velocity);
    auto iconPos = VGet(m_position.x, m_position.y + 50.0f, m_position.z);
    m_pBoxCollider->UpdatePosition(m_position);

    // 向きに合わせてモデル回転
    MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
    VECTOR negativeVec = VTransform(m_dir, rotYMat);

    // モデルに回転をセットする
    MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    m_pBoxCollider->CollisionInit();
    ColliderManager::OnCollisionEnter(m_pBoxCollider);
    // ３Dモデルのポジション設定
    MV1SetPosition(m_modelHandle, m_position);
    MV1SetPosition(m_iconHandle, iconPos);
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Draw()
{
    // モデルとアイコンを描画
    MV1DrawModel(m_modelHandle);
    MV1DrawModel(m_iconHandle);
}

//-----------------------------------------------------------------------------
// @brief  アニメーション処理.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Animation()
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

//-----------------------------------------------------------------------------
// @brief  押し戻し処理.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::PushbackVolume()
{
    // 壁に当たったら速度反転
    if (m_pBoxCollider->GetOnCollisionTag() == ObjectTag::Wall)
    {
        m_velocity = VScale(m_velocity, -1.0f);
    }

    // プレイヤーと当たった
    if (m_pBoxCollider->GetOnCollisionTag() == ObjectTag::Player)
    {
        m_isCollisionPlayer = true;
    }

    // 衝突判定時に呼び出す用
    // 当たっているためめり込み量押し戻して上げる
    m_position = VAdd(m_position, m_pBoxCollider->GetCollisionInfo().m_fixVec);
}

void WalkAroundEnemy::Move()
{
    // 時間経過で移動をさせる
    m_timer++;
    if (m_timer > 360)
    {
        m_timer = 0;
    }
    if (m_timer % 60 == 0)
    {
        auto flag = GetRand(3);
        if (flag == 0)
        {
            m_velocity = VGet(0.0f, 0.0f, 1.0f);
        }
        if(flag == 1)
        {
            m_velocity = VGet(1.0f, 0.0f, 0.0f);
        }
        if (flag == 2)
        {
            m_velocity = VGet(0.0f, 0.0f, -1.0f);
        }
        if (flag == 3)
        {
            m_velocity = VGet(-1.0f, 0.0f, 0.0f);
        }
    }

    m_animType = Walk;
    // 左右・前後同時押しなどで入力ベクトルが0の時は無視
    if (VSquareSize(m_velocity) < 0.5f)
    {
        return;
    }

    // 方向を正規化
    m_velocity = VNorm(m_velocity);

    // 入力方向は現在向いている向きと異なるか
    if (IsNearAngle(m_velocity, m_dir))
    {
        m_dir = m_velocity;
    }
    else
    {
        m_rotateNow = true;
        m_aimDir = m_velocity;
    }
}

//-----------------------------------------------------------------------------
// @brief  回転処理.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Rotate()
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
            // 目標ベクトルに10度だけ近づけた角度
            m_dir = interPolateDir;
        }
    }
}

//-----------------------------------------------------------------------------
// @brief  二つのベクトルの角度が同じか.
//-----------------------------------------------------------------------------
bool WalkAroundEnemy::IsNearAngle(const VECTOR& v1, const VECTOR& v2)
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
float WalkAroundEnemy::CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
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
// @brief  nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する..
//-----------------------------------------------------------------------------
VECTOR WalkAroundEnemy::RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
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
