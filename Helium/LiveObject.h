#pragma once

#include "Head.h"

class CLiveObject
{
private:
	int m_iHealth;
	D3DXVECTOR2 m_vPos;
	float m_fRadius;

protected:
	void Move(float dx, float dy);
	void Move(const D3DXVECTOR2 delta);
	void MoveTo(const D3DXVECTOR2 pos);
	CSprite	m_Sprite;

public:
	CLiveObject(D3DXVECTOR2 pos, int iHealth = 100);
	virtual ~CLiveObject(void);
	void Draw();
	void DoDamage(const int iDamage);
	bool IsAlive() const;
	D3DXVECTOR2 GetPos() const;
	float GetRadius() const;
	int GetHealth() const;
	bool TestCollision(const CLiveObject& obj) const;
};