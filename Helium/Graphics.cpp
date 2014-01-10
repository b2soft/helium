#include "Head.h"

CGraphics::CGraphics(void)
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
}

CGraphics::~CGraphics(void)
{

}

bool CGraphics::Init(HWND hRenderWnd, int width, int height)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
		return FALSE;

	m_d3dpp.BackBufferWidth	=	width;
	m_d3dpp.BackBufferHeight =	height;
	m_d3dpp.BackBufferCount =	1;
	m_d3dpp.Windowed =			1;
	m_d3dpp.BackBufferFormat =	D3DFMT_A8R8G8B8;
	m_d3dpp.SwapEffect =		D3DSWAPEFFECT_DISCARD;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dpp.PresentationInterval =	 D3DPRESENT_INTERVAL_ONE;

	HRESULT hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hRenderWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_pD3DDevice);
	if (FAILED(hr))
		return FALSE;
	return TRUE;
}

void CGraphics::CleanUp()
{
	vecTextures::iterator itr = m_vecTextures.begin();
	while (itr != m_vecTextures.end())
	{
		(*itr)->Release();
		itr++;
	}
	m_vecTextures.clear();

	vecShaders::iterator itr2 = m_vecShaders.begin();
	while (itr2 != m_vecShaders.end())
	{
		(*itr2)->Release();
		itr2++;
	}
	m_vecShaders.clear();
	
	if (m_pD3DDevice)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	if (m_pD3D)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

bool CGraphics::StartRender(D3DCOLOR bgColor)
{
	if (FAILED(m_pD3DDevice->BeginScene()))
		return false;

	if (FAILED(m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, bgColor, 1, 0)))
		return false;

	return true;
}

HRESULT CGraphics::SetFVF(DWORD FVF)
{
	return m_pD3DDevice->SetFVF(FVF);
}

HRESULT CGraphics::SetTexture(DWORD stage, PCTexture pTex)
{
	if (pTex)
		return m_pD3DDevice->SetTexture(stage, pTex->GetTexture());

	return m_pD3DDevice->SetTexture(stage, NULL);
}

bool CGraphics::EndRender()
{
	m_pD3DDevice->EndScene();

	HRESULT hr = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	if (hr==D3DERR_DEVICELOST)
		Reset();

	if (FAILED(hr))
		return false;

	return true;
}

LPDIRECT3DDEVICE9 CGraphics::GetDevice()
{
	return m_pD3DDevice;
}

PCTexture CGraphics::LoadTexture(const std::wstring& strFileName)
{
	vecTextures::iterator itr = m_vecTextures.begin();
	while (itr != m_vecTextures.end())
	{
		if ((*itr)->GetSrc().compare(strFileName) == 0)
			return *itr;
		itr++;
	}
	//if not found
	LPDIRECT3DTEXTURE9 pTex = NULL;

	if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, strFileName.c_str(), &pTex)))
		return NULL;

	PCTexture pTextPtr = new CTexture();
	pTextPtr->SetSrc(strFileName);
	pTextPtr->SetTexture(pTex);

	m_vecTextures.push_back(pTextPtr);
	return pTextPtr;
}

HRESULT CGraphics::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pD3DDevice->SetRenderState(State, Value);
}

HRESULT CGraphics::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pD3DDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT CGraphics::DPUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pD3DDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT CGraphics::SetPixelShader(PCShader shader)
{
	return m_pD3DDevice->SetPixelShader(shader->GetPixelShader());
}

HRESULT CGraphics::SetVertexShader(PCShader shader)
{
	return m_pD3DDevice->SetVertexShader(shader->GetVertexShader());
}

PCShader CGraphics::LoadShader(const std::string& strFileName, const std::string& strFuncName, const std::string& profile)
{
	PCShader pShader = new CShader();

	if (FAILED(pShader->Load(strFileName, strFuncName, profile)))
		return NULL;
	
	LPD3DXBUFFER pShaderBuff = pShader->GetCompiledBuffer();

	if (pShader->IsPS()) //creating pixel shader
	{
		LPDIRECT3DPIXELSHADER9 pPixelShader;
		m_pD3DDevice->CreatePixelShader((DWORD*)pShaderBuff->GetBufferPointer(), &pPixelShader);
		pShader->SetHardwareShader(m_pD3DDevice, pPixelShader);
	}
	else
	{
		LPDIRECT3DVERTEXSHADER9 pVertexShader;
		m_pD3DDevice->CreateVertexShader((DWORD*)pShaderBuff->GetBufferPointer(), &pVertexShader);
		pShader->SetHardwareShader(m_pD3DDevice, pVertexShader);
	}

	m_vecShaders.push_back(pShader);
	return pShader;
}

HRESULT CGraphics::Reset()
{
	vecTextures::iterator itr = m_vecTextures.begin();

	while (itr != m_vecTextures.end())
	{
		(*itr)->Release();
		itr++;
	}

	HRESULT hr = m_pD3DDevice->Reset(&m_d3dpp);
	if (FAILED(hr))
		return hr;

	//realoding textures

	itr = m_vecTextures.begin();
	while (itr != m_vecTextures.end())
	{
		(*itr)->Reload(m_pD3DDevice);
		itr++;
	}

	return D3D_OK;
}

HRESULT CGraphics::DrawSprite(PCTexture pTex, D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	SetTexture(0, pTex);
	float x0 = pos.x + .5;
	float y0 = pos.y + .5;
	float x1 = pos.x + size.x + .5;
	float y1 = pos.y + size.y + .5;

	VertPosTc v[] =
	{
		VertPosTc(D3DXVECTOR3(x0, y0, 0), D3DXVECTOR2(0, 0)),
		VertPosTc(D3DXVECTOR3(x1, y0, 0), D3DXVECTOR2(1, 0)),
		VertPosTc(D3DXVECTOR3(x0, y1, 0), D3DXVECTOR2(0, 1)),
		VertPosTc(D3DXVECTOR3(x1, y1, 0), D3DXVECTOR2(1, 1))
	};
	SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	return DPUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(VertPosTc));
}





