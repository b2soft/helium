#include "Head.h"


CPlayerShip::CPlayerShip()
: CLiveObject(D3DXVECTOR2(0, 200)/*�����. ���.*/, 100/*���. �����*/),
m_Sprite(L"Data/ship-02.png", 0, 0, 64, 64, 32, 32)
{
}

CPlayerShip::~CPlayerShip(void)
{
}

void CPlayerShip::Draw()
{
	// ������ ������
	D3DXVECTOR2 pos = GetPos();
	m_Sprite.Draw(pos);
}

void CPlayerShip::Scroll(float dx, float dy)
{
	D3DXVECTOR2 pos = GetPos();
	pos.x += dx;
	pos.y += dy;
	pos.x = min(max(pos.x, -360), 360);
	pos.y = min(max(pos.y, -250), 250);
	MoveTo(D3DXVECTOR2(pos.x, pos.y));
}