#include "Head.h"

void FireEnemy(D3DXVECTOR2 pos, D3DXVECTOR2 speed);

CEnemy::CEnemy(void)
: CLiveObject(D3DXVECTOR2((rand() % 700) - 350.0f, -400.0f)/*старт. поз.*/, 50/*нач. жизни*/)
, m_Sprite(L"Data/enemy-01.png", 0, 0, 64, 64, 32, 32),
fFireTimeOut(0)
{

}



CEnemy::~CEnemy(void)
{
	
}

void CEnemy::Draw()
{
	D3DXVECTOR2 pos = GetPos();
	m_Sprite.Draw(pos);
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

