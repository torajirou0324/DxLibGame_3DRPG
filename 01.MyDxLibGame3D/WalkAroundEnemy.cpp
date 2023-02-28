//-----------------------------------------------------------------------------
// @brief  �}�b�v��p�j����G�N���X.
//-----------------------------------------------------------------------------
#include "WalkAroundEnemy.h"

#include "ColliderManager.h"

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
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
    // ���f�������[�h
    m_modelHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::Deamon));
    // �����ɍ��킹�ă��f����]

    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(m_modelHandle, m_position);
    // ���f���̑傫�����Z�b�g
    MV1SetScale(m_modelHandle, VGet(0.2f, 0.20f, 0.2f));

    int GraphHandle1 = AssetManager::UseImage(AssetManager::DeamonTexture1);
    int GraphHandle2 = AssetManager::UseImage(AssetManager::DeamonTexture2);
    int GraphHandle3 = AssetManager::UseImage(AssetManager::DeamonTexture3);
    MV1SetTextureGraphHandle(m_modelHandle, 0, GraphHandle1, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 1, GraphHandle2, TRUE);
    MV1SetTextureGraphHandle(m_modelHandle, 2, GraphHandle3, TRUE);

    // �A�j���[�V������ۑ�
    m_animHandle[0] = AssetManager::UseModel(AssetManager::AnimIdle);
    m_animHandle[1] = AssetManager::UseModel(AssetManager::AnimWalk);
    m_animHandle[2] = AssetManager::UseModel(AssetManager::AnimAttack);
    m_animHandle[3] = AssetManager::UseModel(AssetManager::AnimDamage);
    m_animHandle[4] = AssetManager::UseModel(AssetManager::AnimDeath);

	// �A�j���[�V�����̏�����
	MV1DetachAnim(m_modelHandle, 0);
	auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
	m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
	m_animTime = 0.0f;
	m_beforeAnimType = m_animType;
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
WalkAroundEnemy::~WalkAroundEnemy()
{
	MV1DeleteModel(m_modelHandle);
    if (m_pBoxCollider != nullptr)
    {
        ColliderManager::RemoveColliderInfo(m_pBoxCollider);
        delete m_pBoxCollider;
    }
}

//-----------------------------------------------------------------------------
// @brief  ����������.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Init(const VECTOR& _pos, int _ownLevel, int _otherLevel)
{
    m_level = _ownLevel;
    m_velocity = VGet(1.0f, 0.0f, -1.0f);

    // �|�W�V�������Z�b�g
    m_position = _pos;
    // ��������
    m_dir = VGet(0.0f, 0.0f, -1.0f);
    // �G�̐��𗐐��ŃZ�b�g
    m_num = GetRand(2) + 1;

    // �R���C�_�[���Z�b�g
    m_pBoxCollider = new BoxCollider;
    m_pBoxCollider->Init(m_position, VGet(20.0f, 50.0f, 20.0f), ObjectTag::Enemy, std::bind(&WalkAroundEnemy::PushbackVolume, this));
    ColliderManager::AddColliderInfo(m_pBoxCollider);

    // �v���C���[�Ƃ̃��x����r���Ď��o�I�ɋ������ǂ�����m�点�邽�߂ɃA�C�R�����Z�b�g
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
// @brief  �X�V����.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Update()
{
    Move();             // �ړ�
    Rotate();			// ��]
    Animation();		// �A�j���[�V����

    m_position = VAdd(m_position, m_velocity);
    auto iconPos = VGet(m_position.x, m_position.y + 50.0f, m_position.z);
    m_pBoxCollider->UpdatePosition(m_position);

    // �����ɍ��킹�ă��f����]
    MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
    VECTOR negativeVec = VTransform(m_dir, rotYMat);

    // ���f���ɉ�]���Z�b�g����
    MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    m_pBoxCollider->CollisionInit();
    ColliderManager::OnCollisionEnter(m_pBoxCollider);
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(m_modelHandle, m_position);
    MV1SetPosition(m_iconHandle, iconPos);
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Draw()
{
    // ���f���ƃA�C�R����`��
    MV1DrawModel(m_modelHandle);
    MV1DrawModel(m_iconHandle);
}

//-----------------------------------------------------------------------------
// @brief  �A�j���[�V��������.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Animation()
{
    // �A�j���[�V�����J��Ԃ�����
    if (m_animTotalTime < m_animTime)
    {
        m_animTime = 0.0f;
    }

    // �A�j���[�V�����؂�ւ�����
    if (m_animType != m_beforeAnimType)
    {
        MV1DetachAnim(m_modelHandle, 0);
        auto attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animHandle[m_animType]);
        m_animTotalTime = MV1GetAnimTotalTime(m_animHandle[m_animType], attachIndex);
        m_animTime = 0.0f;
        m_beforeAnimType = m_animType;
    }

    // ���݂̃A�j���[�V�����t���[�������f���ɃA�^�b�`����
    MV1SetAttachAnimTime(m_modelHandle, 0, m_animTime);

    // �A�j���[�V�����t���[�����Z
    m_animTime += 0.3f;
}

//-----------------------------------------------------------------------------
// @brief  �����߂�����.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::PushbackVolume()
{
    // �ǂɓ��������瑬�x���]
    if (m_pBoxCollider->GetOnCollisionTag() == ObjectTag::Wall)
    {
        m_velocity = VScale(m_velocity, -1.0f);
    }

    // �v���C���[�Ɠ�������
    if (m_pBoxCollider->GetOnCollisionTag() == ObjectTag::Player)
    {
        m_isCollisionPlayer = true;
        m_pBoxCollider->SetOnCollisionFlag(false);
    }

    // �Փ˔��莞�ɌĂяo���p
    // �������Ă��邽�߂߂荞�ݗʉ����߂��ďグ��
    m_position = VAdd(m_position, m_pBoxCollider->GetCollisionInfo().m_fixVec);
    m_pBoxCollider->UpdatePosition(m_position);
}

void WalkAroundEnemy::Move()
{
    // ���Ԍo�߂ňړ���������
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
    // ���E�E�O�㓯�������Ȃǂœ��̓x�N�g����0�̎��͖���
    if (VSquareSize(m_velocity) < 0.5f)
    {
        return;
    }

    // �����𐳋K��
    m_velocity = VNorm(m_velocity);

    // ���͕����͌��݌����Ă�������ƈقȂ邩
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
// @brief  ��]����.
//-----------------------------------------------------------------------------
void WalkAroundEnemy::Rotate()
{
    if (m_rotateNow)
    {
        // ��]���ڕW�p�x�ɓ��B����Ή�]���[�h�I��
        if (IsNearAngle(m_aimDir, m_dir))
        {
            m_dir = m_aimDir;
            m_rotateNow = false;
        }
        else
        {
            // ��]
            VECTOR interPolateDir;
            interPolateDir = RotateForAimVecYAxis(m_dir, m_aimDir, 10.0f);

            // ��]���ڕW�p�x�𒴂��Ă��Ȃ���
            VECTOR cross1, cross2;
            cross1 = VCross(m_dir, m_aimDir);
            cross2 = VCross(interPolateDir, m_aimDir);

            // �ڕW�p�x�𒴂�����I��
            if (cross1.y * cross2.y < 0.0f)
            {
                interPolateDir = m_aimDir;
                m_rotateNow = false;
            }
            // �ڕW�x�N�g����10�x�����߂Â����p�x
            m_dir = interPolateDir;
        }
    }
}

//-----------------------------------------------------------------------------
// @brief  ��̃x�N�g���̊p�x��������.
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
// @brief  nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�(Y��).
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
// @brief  nowVec����aimVec�Ɍ�������degreeVelocity�̑��x��Y����]����..
//-----------------------------------------------------------------------------
VECTOR WalkAroundEnemy::RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
{
    // �p���x�i�x���j�����W�A���p�ɕϊ��A�E��肩����肩�𒲂ׂ�
    float rotRadian = (DX_PI_F * degreeVelocity / 180.0f);
    rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

    // Y����]�s����쐬����
    MATRIX yRotMat = MGetRotY(rotRadian);

    // Y����]����
    VECTOR rotVec;
    rotVec = VTransform(nowVec, yRotMat);
    return rotVec;
}
