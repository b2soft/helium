#pragma once

#include "Head.h"

class CEnemy :public CLiveObject
{
	CSprite m_Sprite;

	float fFireTimeOut;//timeout for firing

public:
	CEnemy(void);
	virtual ~CEnemy(void);
	void Draw();
	void Update(float fDeltaTime);
};