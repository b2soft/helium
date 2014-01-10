#pragma once

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

using namespace std;

#include "Utils.h"

#include "Singleton.h"
#include "Shader.h"
#include "Texture.h"
#include "Graphics.h"


#include "LiveObject.h"
#include "PlayerShip.h"

#include "StarField.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Text.h"
#include "System.h"