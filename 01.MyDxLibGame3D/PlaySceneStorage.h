#pragma once
#include <memory>
#include <map>
#include "PlayScene.h"

class CharacterStorage
{
private:
    PlayScene* GameContainer;

public:
    PlayScene*& GetNomalState() { return GameContainer; }
};