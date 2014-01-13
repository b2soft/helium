#pragma once

#include "Head.h"

class CStarField
{
	PCTexture m_pTex;
	
	float m_fDT;

	struct Star //one star
	{
		D3DXVECTOR2 m_pos;//position of star
		int m_size;//size of star
		Star(D3DXVECTOR2 pos = D3DXVECTOR2(0, 0), int size = 8);
	};
	std::vector<Star> m_vecStars;

public:
	CStarField(void);
	~CStarField(void);
	void Update(float fDeltaTime);
	void Draw();
};