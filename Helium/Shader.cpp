#include "Head.h"


CShader::CShader()
: m_bIsPS(true),
m_pErrors(NULL),
m_pShaderBuff(NULL),
m_pConstantTable(NULL)
{
	m_pShader.m_pPixelShader	= NULL;
	m_pShader.m_pVertexShader	= NULL;
}

CShader::~CShader()
{
	Release();
}

HRESULT CShader::Release()
{
	if (m_pConstantTable)
		m_pConstantTable->Release();
	m_pConstantTable = NULL;

	if (m_pShaderBuff)
		m_pShaderBuff->Release();
	m_pShaderBuff = NULL;

	if (m_pErrors)
		m_pErrors->Release();
	m_pErrors = NULL;

	return D3D_OK;
}

HRESULT CShader::Load(const std::string& strFileName, const std::string& strFuncName, const std::string& profile)
{
	std::string src = GetFileAsString(strFileName);
	//compiling the shader code
	HRESULT hr = D3DXCompileShader(src.c_str(), src.length(), NULL, NULL, strFuncName.c_str(), profile.c_str(), D3DXSHADER_OPTIMIZATION_LEVEL3, &m_pShaderBuff, &m_pErrors, &m_pConstantTable);
	if (FAILED(hr))
		return hr;

	if (profile[0] == 'p')
		m_bIsPS = true;
	else
		m_bIsPS = false;
	
	return D3D_OK;
}

void CShader::SetHardwareShader(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DPIXELSHADER9 pHWShader)
{
	m_pShaderDevice = pDevice;
	m_pShader.m_pPixelShader = pHWShader;
}

void CShader::SetHardwareShader(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXSHADER9 pHWShader)
{
	m_pShaderDevice = pDevice;
	m_pShader.m_pVertexShader = pHWShader;
}

HRESULT CShader::SetFloat(D3DXHANDLE hConstant, CONST FLOAT Value)
{
	return m_pConstantTable->SetFloat(m_pShaderDevice, hConstant, Value);
}

HRESULT CShader::SetVector(D3DXHANDLE hConstant, CONST D3DXVECTOR4* pVec4)
{
	return m_pConstantTable->SetVector(m_pShaderDevice, hConstant, pVec4);
}

HRESULT CShader::SetMatrix(D3DXHANDLE hConstant, CONST D3DXMATRIX* pMatrix)
{
	return m_pConstantTable->SetMatrix(m_pShaderDevice, hConstant, pMatrix);
}

LPDIRECT3DPIXELSHADER9 CShader::GetPixelShader()
{
	return m_pShader.m_pPixelShader;
}

LPDIRECT3DVERTEXSHADER9 CShader::GetVertexShader()
{
	return m_pShader.m_pVertexShader;
}

bool CShader::IsPS()
{
	return m_bIsPS;
}

bool CShader::IsVS()
{
	return !m_bIsPS;
}

LPD3DXBUFFER CShader::GetCompiledBuffer()
{
	return m_pShaderBuff;
}

