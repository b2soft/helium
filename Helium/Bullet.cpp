#include "Head.h"


CBullet::CBullet(D3DXVECTOR2 pos, D3DXVECTOR2 speed, const std::wstring& strTexFile)
: m_pos(pos), m_speed(speed), m_iDamage(30),
m_Sprite(strTexFile, 0, 0, 16, 32, 8, 16)
{
	//m_pTex = CGraphics::get().LoadTexture(strTexFile);
}

CBullet::~CBullet(void)
{

}

D3DXVECTOR2 CBullet::GetPos() const
{
	return m_pos;
}

void CBullet::Update(float fDeltaTime)
{
	m_pos += m_speed * fDeltaTime;
}

bool CBullet::TestCollision(const CLiveObject& obj) const
{
	D3DXVECTOR2 distance = obj.GetPos() - GetPos();

	if (obj.GetRadius() >= D3DXVec2Length(&distance))
		return true;

	return false;
}

int CBullet::GetDamage() const
{
	return m_iDamage;
}

void CBullet::Draw() const
{
	D3DXVECTOR2 pos = GetPos();
	//CGraphics::get().SetTexture(0, m_pTex);
	//CGraphics::get().DrawSprite(m_pTex, pos - D3DXVECTOR2(8, 8), D3DXVECTOR2(16, 32));
	m_Sprite.Draw(pos);
}
