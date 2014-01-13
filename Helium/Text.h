#pragma once

#include "Head.h"

class CText
{
	float m_fTimeLife;
	std::string m_sText;
	D3DXVECTOR2 m_pos;
	ID3DXFont *m_font;
	int m_iSize;
	D3DXCOLOR m_color;

public:
	CText();
	CText(D3DXVECTOR2 pos, string text, int size, D3DXCOLOR m_color);
	~CText();
	void Draw();
	void Update(std::string text);
};