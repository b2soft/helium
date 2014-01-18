#pragma once

#include "Head.h"

class CClock
{
private:

	float m_dt;
	//DWORD m_PrevTime;
	LARGE_INTEGER m_iPrevTime;
	LARGE_INTEGER m_iCurrTime;
	LARGE_INTEGER m_iFreq;
	double m_fFreq;

public:
	CClock();
	void Initialize();
	float Update();
	float DT() const;
};