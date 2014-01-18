#include "Head.h"
const float divider = 800.0f;

CClock::CClock()
{
	
}

float CClock::Update()
{
	QueryPerformanceCounter(&m_iCurrTime);
	m_dt = (m_iCurrTime.QuadPart - m_iPrevTime.QuadPart)/m_fFreq;
	m_iPrevTime = m_iCurrTime;
	
	return m_dt/divider;
}

float CClock::DT() const
{
	return m_dt/divider;
}

void CClock::Initialize()
{
	QueryPerformanceCounter(&m_iPrevTime);
	QueryPerformanceFrequency(&m_iFreq);

	m_fFreq = (float)m_iFreq.QuadPart / 1000.0;
}

