#include "Head.h"


CLiveObject::CLiveObject(D3DXVECTOR2 pos, int iHealth /*= 100*/)
{
	m_vPos = pos;
	m_iHealth = iHealth;
	m_fRadius = 28;
}

CLiveObject::~CLiveObject(void)
{

}

void CLiveObject::DoDamage(const int iDamage)
{
	m_iHealth -= iDamage;
}

bool CLiveObject::IsAlive() const
{
	return (m_iHealth > 0);
}

void CLiveObject::Move(float dx, float dy)
{
	Move(D3DXVECTOR2(dx, dy));
}

void CLiveObject::Move(const D3DXVECTOR2 delta)
{
	m_vPos += delta;
}

void CLiveObject::MoveTo(const D3DXVECTOR2 pos)
{
	m_vPos = pos;
}

D3DXVECTOR2 CLiveObject::GetPos() const
{
	return m_vPos;
}

bool CLiveObject::TestCollision(const CLiveObject& obj) const
{
	D3DXVECTOR2 distance = obj.GetPos() - GetPos();

	if (obj.GetRadius() + GetRadius() >= D3DXVec2Length(&distance))
		return true;

	return false;
}

float CLiveObject::GetRadius() const
{
	return m_fRadius;
}

