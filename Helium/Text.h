#pragma once

#include "Head.h"

class CText
{
	float m_fTimeLife;
	std::wstring m_sText;
	D3DXVECTOR2 m_pos;

public:
	CText();
	~CText();
	void Draw() const;
};