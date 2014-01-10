#pragma once

#include "Head.h"

class CGraphics;

class CTexture
{
	friend class �Graphics;

private:
	//! ���� ��������
	std::wstring m_strTexSrc;
	//! ��� ���� ��������
	LPDIRECT3DTEXTURE9 m_pTex;

	D3DSURFACE_DESC m_ddesc;

protected:
	// ������ ������ ��� ������ Graphics
	CTexture(void);
	~CTexture(void);
	HRESULT Release();
	void SetTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetSrc(const std::wstring& src);
	LPDIRECT3DTEXTURE9 GetTexture() const;
	HRESULT Reload(LPDIRECT3DDEVICE9 pDev);

public:
	std::wstring GetSrc() const;
	UINT GetWidth() const;
	UINT GetHeight() const;
};

typedef CTexture* PCTexture; //pointer type to a CTexture