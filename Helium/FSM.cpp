#include "Head.h"

CFsm::CFsm()
{
	m_eState = PLAY;
}

CFsm::~CFsm()
{

}

STATE CFsm::GetState()
{
	return m_eState;
}

void CFsm::SetState(STATE state)
{
	m_eState = state;
}
