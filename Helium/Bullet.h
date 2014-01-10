#pragma once

#include "Head.h"


class CBullet
{
	int m_iDamage;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_speed;

	//PCTexture m_pTex;
	CSprite	m_Sprite;

public:
	CBullet(D3DXVECTOR2 pos = D3DXVECTOR2(0, 0), D3DXVECTOR2 speed = D3DXVECTOR2(0, 0), const std::wstring& strTexFile = L"Data/bullet.dds");
	~CBullet(void);
	D3DXVECTOR2 GetPos() const;
	void Draw() const;
	int GetDamage() const;
	void Update(float fDeltaTime);
	bool TestCollision(const CLiveObject& obj) const;
};

