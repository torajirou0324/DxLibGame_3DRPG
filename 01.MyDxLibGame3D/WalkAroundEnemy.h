//-----------------------------------------------------------------------------
// @brief  �}�b�v��p�j����G�N���X.
//-----------------------------------------------------------------------------
#pragma once
#include "Character.h"
#include "BoxCollider.h"

class WalkAroundEnemy
{
public:
    WalkAroundEnemy();
    ~WalkAroundEnemy();

    void Init(const VECTOR& _pos, int _ownLevel, int _otherLevel);
    void Update();
    void Draw();
    void Animation();		// �A�j���[�V��������.

    // �Q�b�^�[
    // ���x��
    const int& GetLevel() { return m_level; }
    // �o���G�̑���
    const int& GetEnemyNum() { return m_num; }

    // �v���C���[�Ɠ������Ă��邩�̃t���O
    const bool& GetIsCollisionPlayerFlag() { return m_isCollisionPlayer; }
private:
    // �߂荞�݂̉����߂��ʂ�������(�����蔻��)
    void PushbackVolume();

    void Move();
    void Rotate();
    // ��̃x�N�g���̊p�x��������.
    bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
    // nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�(Y��).
    float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
    // nowVec����aimVec�Ɍ�������degreeVelocity�̑��x��Y����]����.
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

    int m_animHandle[5];	    // �A�j���[�V�����̃��f���n���h��.
    int m_modelHandle;          // �L�����N�^�[���g�̃��f���n���h��.
    int m_iconHandle;           // ���̏�̃A�C�R���̃��f���n���h��.
    int m_level;                // �������邽�߂̍ő僌�x���l.
    int m_num;                  // �������邽�߂̓G�̍ő吔(3�̂܂�).

    int m_timer;

    float m_animTime;           // �A�j���[�V�����̌o�ߎ���.
    float m_animTotalTime;      // �A�j���[�V�����̑��Đ�����.

    bool m_rotateNow;		    // ��]��������p.
    bool m_isCollisionPlayer;   // �v���C���[�Ɠ���������.

    VECTOR m_position;      // ���W.
    VECTOR m_rotate;		// �p�x.
    VECTOR m_velocity;		// ���x.
    VECTOR m_dir;			// ����.
    VECTOR m_aimDir;		// �ڕW����.

    BoxCollider* m_pBoxCollider;

    Anim m_animType;            // ���݂̃A�j���[�V�����ۑ��p.
    Anim m_beforeAnimType;      // 1�O�̃A�j���[�V�����ۑ��p.
};