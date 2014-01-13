#include "Head.h"

CText::CText()
{
}

CText::CText(D3DXVECTOR2 pos, string text, int size, D3DXCOLOR color)
{
	HRESULT hr;
	D3DXFONT_DESCA lf;

	m_iSize = size;
	m_color = color;
	m_pos = pos;
	m_sText = text;

	lf.Height = size;
	//lf.Width = size;
	lf.Weight = 400;//max thickness - 0, min - 1000
	lf.Italic = false;
	lf.CharSet = DEFAULT_CHARSET;
	lf.Quality = 100;
	strcpy(lf.FaceName, "Arial");

	m_font = 0;

	D3DXCreateFontIndirectA(CGraphics::get().GetDevice(), &lf, &m_font);
}

void CText::Draw()
{
	RECT rect;

	rect.top = m_pos.y;
	rect.left = m_pos.x;
	rect.bottom = WINDOW_HEIGHT;
	rect.right = WINDOW_WIDTH;

	m_font->DrawTextA(NULL, m_sText.c_str(), -1, &rect, DT_LEFT, m_color);
}

CText::~CText()
{
	if (m_font != NULL)
	{
		m_font->Release(); //release font
		m_font = NULL;
	}
}

void CText::Update(std::string text)
{
	m_sText = text;
}


