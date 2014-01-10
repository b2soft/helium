#pragma once

#include "Head.h"

class CGraphics;

class CTexture
{
	friend class CGraphics;

private:
	std::wstring m_strTexSrc;	//File with a texture
	LPDIRECT3DTEXTURE9 m_pTex;	//texture variable

	D3DSURFACE_DESC m_ddesc;


protected:
	CTexture(void);
	~CTexture(void);

	HRESULT Release();
	HRESULT Reload(LPDIRECT3DDEVICE9 pDevice);
	void SetTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetSrc(const std::wstring& src);
	LPDIRECT3DTEXTURE9 GetTexture() const;

public:
	std::wstring GetSrc() const;
	UINT GetWidth() const;
	UINT GetHeight() const;
};

typedef CTexture* PCTexture; //pointer type to a CTexture