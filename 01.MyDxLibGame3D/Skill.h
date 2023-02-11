#pragma once
#include <string>

enum AttributeType
{
    Physical,   // �����^�C�v
    Special,    // ���@�^�C�v
    Recovery    // �񕜃^�C�v
};

// �Z�ɕK�v�ȏ��i�[�p�\����
struct SKILL
{
    std::string SkillName;      // �Z��
    AttributeType SkillType;    // �Z�̑���
    int AffectsSpeed;           // �Z���L�̑f�������Z���Z�{�[�i�X�l
    int Power;                  // �����ł���΍U���З́A���@�ł���Ζ��@�З�
    bool PowerType;             // true���ƕ����Afalse���Ɩ��@�B���������@������p�t���O
};

//SKILL Skill[] =
//{
//    {"���肳��",Physical,0,60,true},
//    {"�t���A",Special,2,30,false},
//    {"�q�[��",Recovery,2,30,false},
//    {"�T���_�[",Special,5,50,false},
//};