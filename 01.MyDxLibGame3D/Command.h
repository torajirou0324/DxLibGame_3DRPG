#pragma once
#include <string>
#include <functional>
#include <DxLib.h>
#include "Player.h"
#include "Input.h"
#include "AssetManager.h"

enum TAG_Command
{
    AttackCommand,
    IntelligenceCommand,
    OnThingsCommand,
    Return,
};

class Command
{
public:
    virtual ~Command() {
    }
    virtual void Execute() const = 0;
    virtual void Draw(int posY) const = 0;
};