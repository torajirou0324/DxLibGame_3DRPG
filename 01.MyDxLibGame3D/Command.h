#pragma once
#include <functional>
#include <string>
#include <DxLib.h>
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "AssetManager.h"
#include "ArrowSymbol.h"

enum TAG_CommandState
{
    TAG_isPlay,         // �퓬���邩���Ȃ���
    TAG_isMoveType,     // �s���̃^�C�v
    TAG_isAttackSkill,  // �U���̋Z�I��
    TAG_isMagicSkill,   // ���@�̋Z�I��
    TAG_isTargetAttack, // �U���ڕW�̑I��
    TAG_Max,            // �R�}���h�I���̑J�ڕK�v������
    TAG_None,           // �J�ڕύX�Ȃ��ʒm�p�^�O
    TAG_Escape,         // ������Ƃ��p
    TAG_ActionCompleted // �R�}���h�I�������ʒm�p
};

class Command
{
public:
    virtual ~Command() {
    }

    virtual void Init(SKILL _skill){}
    virtual void Init(Enemy* _enemy){}
    virtual TAG_CommandState Execute() = 0;
    virtual void Draw(int posY) const = 0;

    bool m_display = false;
};