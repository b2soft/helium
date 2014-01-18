#pragma once

#include "Head.h"

class CGraphics : public singleton<CGraphics>
{
	friend class singleton<CGraphics>;
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	D3DPRESENT_PARAMETERS m_d3dpp;

	typedef std::vector<PCTexture> vecTextures;
	vecTextures m_vecTextures;
	
	typedef std::vector<PCShader> vecShaders;
	vecShaders m_vecShaders;

protected:
	CGraphics(void);
	~CGraphics(void);
	
public:
	LPDIRECT3DDEVICE9 GetDevice();
	bool	Init(HWND hRenderWnd, int width, int height);
	void	CleanUp();
	HRESULT Reset();
	bool	StartRender(D3DCOLOR bgColor);
	HRESULT SetFVF(DWORD FVF);
	HRESULT SetPixelShader(PCShader shader);
	HRESULT SetVertexShader(PCShader shader);
	HRESULT SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
	HRESULT SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
	HRESULT SetTexture(DWORD stage, PCTexture pTex);
	HRESULT DPUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
	HRESULT DrawSprite(PCTexture pTex, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	bool	EndRender();
	PCTexture	LoadTexture(const std::wstring& strFileName);
	PCShader	LoadShader(const std::string& strFileName, const std::string& strFuncName, const std::string& profile);
};

