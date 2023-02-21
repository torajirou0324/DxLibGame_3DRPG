#pragma once
#include <functional>
#include <string>
#include <DxLib.h>
#include "Player.h"
#include "Input.h"
#include "AssetManager.h"

enum TAG_Command
{
    IntelligenceCommand,
    AttackCommand,
    Return,
};

class Command
{
public:
    virtual ~Command() {
    }
    virtual void Execute() = 0;
    virtual void Draw(int posY) const = 0;

    bool m_display = false;
};