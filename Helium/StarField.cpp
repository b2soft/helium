#include "Head.h"


CStarField::CStarField(void)
{
	m_fDT = .0f;
	m_pTex = CGraphics::get().LoadTexture(L"Data/star.dds");
}

CStarField::~CStarField(void)
{
	delete m_pTex;
	m_vecStars.clear();
}

void CStarField::Update(float fDeltaTime)
{
	//moving stars
	for (size_t i = 0; i < m_vecStars.size(); i++)
	{
		m_vecStars[i].m_pos.y += m_vecStars[i].m_size * fDeltaTime * 50;
		if (m_vecStars[i].m_pos.y>300)
		{
			m_vecStars[i] = m_vecStars[m_vecStars.size() - 1];
			m_vecStars.resize(m_vecStars.size() - 1);
		}
	}
	//generating new stars if dt > .1 sec
	m_fDT += fDeltaTime;
	while (m_fDT > .1f)
	{
		m_vecStars.push_back(Star(D3DXVECTOR2((rand() % 800) - 400, -300.0), (rand() % 5 + 1)));
		m_fDT -= .1f;
	}

}

void CStarField::Draw()
{
	CGraphics::get().SetTexture(0, m_pTex);

	for (size_t i = 0; i < m_vecStars.size(); i++)
	{
		D3DXVECTOR2 pos = m_vecStars[i].m_pos;
		float size = float(m_vecStars[i].m_size);
		CGraphics::get().DrawSprite(m_pTex, pos, D3DXVECTOR2(size, size));
	}
}

CStarField::Star::Star(D3DXVECTOR2 pos /*= D3DXVECTOR2(0, 0)*/, int size /*= 8*/)
: m_pos(pos), m_size(size)
{

}
