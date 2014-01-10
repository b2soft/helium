#include "Head.h"

void FireEnemy(D3DXVECTOR2 pos, D3DXVECTOR2 speed);

CEnemy::CEnemy(void)
: CLiveObject(D3DXVECTOR2((rand() % 700) - 400.0f, -400.0f)/*старт. поз.*/, 50/*нач. жизни*/)
{
	m_pTex = CGraphics::get().LoadTexture(L"Data/enemy-01.png");
}

CEnemy::~CEnemy(void)
{

}

void CEnemy::Draw()
{
	D3DXVECTOR2 pos = GetPos();
	CGraphics::get().SetTexture(0, m_pTex);
	CGraphics::get().DrawSprite(m_pTex, pos - D3DXVECTOR2(32, 32), D3DXVECTOR2(64, 64));
}

void CEnemy::Update(float fDeltaTime)
{
	Move(0, 100 * fDeltaTime);

	fFireTimeOut -= fDeltaTime;
	if ((fFireTimeOut < 0) && (rand() & 127) == 127)
	{
		FireEnemy(GetPos(), D3DXVECTOR2(0, 200));
		fFireTimeOut = 0.8f; // не сможем стрелять ещё 0.8f секунд
	}
}

