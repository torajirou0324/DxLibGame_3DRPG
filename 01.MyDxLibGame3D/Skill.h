#pragma once
#include <string>

enum class AttributeType
{
    None,       // 初期化用
    Physical,   // 物理タイプ
    Special,    // 魔法タイプ
    Recovery    // 回復タイプ
};

// 技に必要な情報格納用構造体
struct SKILL
{
    std::string SkillName;      // 技名
    AttributeType SkillType;    // 技の特性
    int Power;                  // 物理であれば攻撃威力、魔法であれば魔法威力、回復であれば回復力
    int MagicPower;             // 消費魔力
    int AffectsSpeed;           // 技特有の素早さ加算減算ボーナス値
};

//SKILL Skill[] =
//{
//    {"きりさく",Physical,0,60,true},
//    {"フレア",Special,2,30,false},
//    {"ヒール",Recovery,2,30,false},
//    {"サンダー",Special,5,50,false},
//};