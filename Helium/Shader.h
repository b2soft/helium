#pragma once

#include "Head.h"

class CGraphics;

class CShader
{
	friend class CGraphics;

private:
	bool m_bIsPS;				//is a Pixel Shader?

	LPD3DXBUFFER m_pErrors;		//Errors of compilating shaders
	LPD3DXBUFFER m_pShaderBuff;	//Compiled Shader
	LPD3DXCONSTANTTABLE m_pConstantTable;

	union //For less memory using
	{
		LPDIRECT3DPIXELSHADER9	m_pPixelShader;
		LPDIRECT3DVERTEXSHADER9 m_pVertexShader;
	} m_pShader;

	LPDIRECT3DDEVICE9 m_pShaderDevice;

protected:
	HRESULT Load(const std::string& strFileName, const std::string& strFuncName, const std::string& profile);
	HRESULT Release();
	LPDIRECT3DPIXELSHADER9		GetPixelShader();
	LPDIRECT3DVERTEXSHADER9		GetVertexShader();
	LPD3DXBUFFER GetCompiledBuffer();//for HW Pixel Shader
	void SetHardwareShader(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DPIXELSHADER9 pHWShader);
	void SetHardwareShader(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXSHADER9 pHWShader);
	CShader();
	~CShader();

public:
	bool IsPS();
	bool IsVS();
	HRESULT SetFloat(D3DXHANDLE hConstant, CONST FLOAT Value);
	HRESULT SetVector(D3DXHANDLE hConstant, CONST D3DXVECTOR4* pVec4);
	HRESULT SetMatrix(D3DXHANDLE hConstant, CONST D3DXMATRIX* pMatrix);
};

typedef CShader* PCShader;//own pointer to CShader