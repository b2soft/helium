#pragma once

#include "Head.h"

class CPlayerShip : public CLiveObject
{
//	PCTexture m_pTex;
	CSprite	m_Sprite;
	
public:
	CPlayerShip(void);
	~CPlayerShip(void);
	void Draw();
	void Scroll(float dx, float dy);
};