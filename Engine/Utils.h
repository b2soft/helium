#pragma once

#include "Head.h"

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_TUTORIAL			107
#define IDI_SMALL				108
#define IDC_TUTORIAL			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif
// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif



string GetFileAsString(const string& strFileName);

struct CPoint
{
	int m_x, m_y;
	CPoint();
	CPoint(int x, int y);
};

struct CRect
{
	CPoint m_min, m_max;
	CRect();
	CRect(CPoint ptmin, CPoint ptMax);
};

struct VertPosDiffuse
{
	D3DXVECTOR3 m_pos;
	D3DCOLOR m_color;
	VertPosDiffuse(D3DXVECTOR3 pos, D3DCOLOR color)
		: m_pos(pos), m_color(color)
	{}
};

struct VertPosTc
{
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_tc;
	VertPosTc() {}
	VertPosTc(D3DXVECTOR3 pos, D3DXVECTOR2 tc)
		: m_pos(pos), m_tc(tc)
	{}
};

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 1
#define _CheckLeaks _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#define _BreakAllock(x) _CrtSetBreakAlloc(x)
#include <stdlib.h>
#include <crtdbg.h>
// Контекст переменной BreakAlloc {,,msvcrtd.dll}_crtBreakAlloc

#define DebugMessage(_Mess) __DebugMessage(_Mess,__FILE__,__FUNCSIG__,__LINE__)
#define BreakOrAssert(_Mess) {DebugMessage(_Mess);DebugBreak();}


inline void __DebugMessage(const char* _Message, const char* _File, const char* _Sign, int _Line)
{
	size_t lv_len = strlen(_Message) + strlen(_File) + strlen(_Sign) + 64;
	char Tmp[1024];
	char* tmp = Tmp;
	if (lv_len > 1024)
		tmp = new char[lv_len];

	sprintf(tmp, "%s\nFile: %s\nFunction: %s\nLine: %i\n", _Message, _File, _Sign, _Line);
	MessageBoxA(0, tmp, "Debug message", MB_OK | MB_ICONINFORMATION);
	if (tmp != Tmp)delete[] tmp;
}
#else
#define _CheckLeaks
#endif
