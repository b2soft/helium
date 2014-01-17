#pragma once

#include "Head.h"

class CClock
{
private:

	float m_dt;
	DWORD m_PrevTime;

public:
	CClock();
	void Initialize();
	float Update();
	float DT() const;
};