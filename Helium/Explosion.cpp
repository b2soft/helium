#include "Head.h"

void CExplosion::Update(float fDeltaTime)
{
	m_fPlayTime += fDeltaTime;
}

void CExplosion::Draw()
{
	m_anim.Draw(m_pos, m_fPlayTime, 2.0f);
}

CExplosion::CExplosion(D3DXVECTOR2 pos)
: m_pos(pos)
{
	for (int y = 0; y < 5; y++)
	for (int x = 0; x < 5; x++)
		m_anim.Add(L"Data/explosion.dds", x * 51, y * 51, 51, 51, x * 51 + 25, y * 51 + 25, .05f);
	m_fPlayTime = .0f;
}

bool CExplosion::IsFinished() const
{
	return (m_anim.GetLength() < m_fPlayTime);
}

CExplosion::~CExplosion()
{

}
