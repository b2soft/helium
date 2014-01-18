#pragma once

#pragma comment (lib, "../Release/Engine.lib")

#include "../Engine/Head.h"

#include "LiveObject.h"
#include "Bullet.h"
#include "Enemy.h"

#include "PlayerShip.h"
#include "Explosion.h"
#include "StarField.h"
#include "Text.h"
#include "System.h"

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
