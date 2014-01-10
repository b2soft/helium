#include "Head.h"


CPlayerShip::CPlayerShip()
: CLiveObject(D3DXVECTOR2(0, 200)/*�����. ���.*/, 100/*���. �����*/)
{
	m_pTex = CGraphics::get().LoadTexture(L"Data/ship-02.png");
}

CPlayerShip::~CPlayerShip(void)
{
}

void CPlayerShip::Draw()
{
	// ������ ������
	D3DXVECTOR2 pos = GetPos();
	CGraphics::get().SetTexture(0, m_pTex);
	CGraphics::get().DrawSprite(m_pTex, pos - D3DXVECTOR2(32, 32)/*���������� ������*/,
		D3DXVECTOR2(64, 64));

}

void CPlayerShip::Scroll(float dx, float dy)
{
	D3DXVECTOR2 pos = GetPos();
	pos.x += dx;
	pos.y += dy;
	pos.x = min(max(pos.x, -350), 350);
	pos.y = min(max(pos.y, -250), 250);
	MoveTo(D3DXVECTOR2(pos.x, pos.y));
}