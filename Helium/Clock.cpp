#include "Head.h"
const float divider = 800.0f;

CClock::CClock()
{
	
}

float CClock::Update()
{
	m_dt = timeGetTime() - m_PrevTime;
	m_PrevTime = timeGetTime();
	
	return m_dt/divider;
}

float CClock::DT() const
{
	return m_dt/divider;
}

void CClock::Initialize()
{
	m_PrevTime = timeGetTime();
}

