#include "Head.h"


CTexture::CTexture(void)
: m_pTex(NULL)
{

}

CTexture::~CTexture(void)
{
	Release();
}

void CTexture::SetTexture(LPDIRECT3DTEXTURE9 pTex)
{
	Release();
	m_pTex = pTex;
}

void CTexture::SetSrc(const std::wstring& src)
{
	m_strTexSrc = src;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture() const
{
	return m_pTex;
}

std::wstring CTexture::GetSrc() const
{
	return m_strTexSrc;
}

HRESULT CTexture::Release()
{
	if (m_pTex)
		m_pTex->Release();
	m_pTex = NULL;

	return D3D_OK;
}

HRESULT CTexture::Reload(LPDIRECT3DDEVICE9 pDevice)
{
	return D3DXCreateTextureFromFile(pDevice, GetSrc().c_str(), &m_pTex);
}
