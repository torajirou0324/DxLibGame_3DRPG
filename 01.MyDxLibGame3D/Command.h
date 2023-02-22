#pragma once
#include <functional>
#include <string>
#include <DxLib.h>
#include "Player.h"
#include "Input.h"
#include "AssetManager.h"

enum TAG_CommandState
{
    TAG_isPlay,         // 戦闘するかしないか
    TAG_isMoveType,     // 行動のタイプ
    TAG_isAttackSkill,  // 攻撃の技選択
    TAG_isMagicSkill,   // 魔法の技選択
    TAG_Max,            // コマンド選択の遷移必要数生成
    TAG_None,           // 遷移変更なし通知用タグ
    TAG_Escape,         // 逃げるとき用
    TAG_ActionCompleted // コマンド選択完了通知用
};

class Command
{
public:
    virtual ~Command() {
    }
    virtual TAG_CommandState Execute() = 0;
    virtual void Draw(int posY) const = 0;

    bool m_display = false;
};