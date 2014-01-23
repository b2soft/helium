#pragma once

#define _SCL_SECURE_NO_WARNINGS
#define _ITERATOR_DEBUG_LEVEL 0

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <mmsystem.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")

#ifdef _DEBUG
#pragma comment (lib, "d3dx9d.lib")
#else
#pragma comment (lib, "d3dx9.lib")
#endif

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma comment (lib, "winmm.lib")

using namespace std;

#include "Utils.h"

#include "Clock.h"
#include "Singleton.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteA.h"
#include "Graphics.h"

