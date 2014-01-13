#pragma once

#include "Head.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SHIP_SPEED 350


class CSystem
{
	
private:
	static bool InitD3D(HWND hWnd, int iWindowWidth, int iWindowHeight);
	static HWND MakeWindow(HINSTANCE hInstance);
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static int MainLoop();
	static void Update(const float fDeltaTime);
	static void DrawSetup();
	static void Draw();
	static void Release();
public:
	static void Initialize(HINSTANCE hInstance);
	
};
