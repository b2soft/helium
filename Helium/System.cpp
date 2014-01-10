#include "Head.h"

CPlayerShip*			g_pPlayer;
CStarField*				g_pStarField;
std::vector<CEnemy>		g_vEnemies;
std::vector<CBullet>	g_vPlayerBullets;
std::vector<CBullet>	g_vEnemyBullets;
int level = 0;

PCShader m_pPixelShader, m_pVertexShader;
HWND m_hWindow;

void FireEnemy(D3DXVECTOR2 pos, D3DXVECTOR2 speed)
{
	g_vEnemyBullets.push_back(CBullet(pos, speed, L"Data/bullet-enemy.dds"));
}

void ProcessUserInput(float fDeltaTime)
{
	int dx = 0;
	if (GetAsyncKeyState(VK_LEFT) & 32768)
		dx--; // �������� �����
	if (GetAsyncKeyState(VK_RIGHT) & 32768)
		dx++; // �������� ������

	if (GetAsyncKeyState(VK_UP) & 32768)
	{
		if (level <= 50)
			level++;
	}


	g_pPlayer->Scroll(dx*SHIP_SPEED*fDeltaTime, 0);

	static float fFireTimeOut = .0f;
	fFireTimeOut -= fDeltaTime;

	if (GetAsyncKeyState(VK_SPACE) & 32768 && fFireTimeOut <= 0) //shoot
	{
		fFireTimeOut = .3f;
		CBullet bullet(g_pPlayer->GetPos() - D3DXVECTOR2(0, 30), D3DXVECTOR2(0, -300));
		g_vPlayerBullets.push_back(bullet);
	}
	if (GetAsyncKeyState(0x51))
		PostQuitMessage(0);
}



HWND CSystem::MakeWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),CS_CLASSDC, wndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"Helium", NULL
	};
	RegisterClassEx(&wc);

	auto hWindow = CreateWindowW(L"Helium", L"Helium", WS_BORDER, 300, 50, WINDOW_WIDTH + 16, WINDOW_HEIGHT + 38, NULL, NULL, NULL, NULL);
	
	ShowWindow(hWindow, SW_SHOW);
	UpdateWindow(hWindow);//update it
	SetForegroundWindow(hWindow);//set as foreground
	SetFocus(hWindow);//give the focus to window
	ShowCursor(false);
	return hWindow;
}

LRESULT CALLBACK CSystem::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ERASEBKGND:
		return TRUE;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

bool CSystem::InitD3D(HWND hWnd, int iWindowWidth, int iWindowHeight)
{
	LPD3DXBUFFER pErrors = NULL;
	LPD3DXBUFFER pShaderBuff = NULL;
	// �������������� �������
	if (!CGraphics::get().Init(hWnd, iWindowWidth, iWindowHeight))
		return FALSE;
	// ��������� ���������� ������
	m_pVertexShader = CGraphics::get().LoadShader("vs.hlsl", "main", "vs_3_0");
	// ��������� ���������� ������
	m_pPixelShader = CGraphics::get().LoadShader("ps.hlsl", "pixel_shader_main", "ps_3_0");

	g_pPlayer = new CPlayerShip();
	g_pStarField = new CStarField();

	return TRUE;
}

void CSystem::Initialize(HINSTANCE hInstance)
{
	m_hWindow = MakeWindow(hInstance);

	InitD3D(m_hWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	MainLoop();
	
}

int CSystem::MainLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			DrawSetup();
		}
	}
	return 1;
}

void CSystem::Update()
{
	ProcessUserInput(.02f);

	if ((rand() & (127 - level)) == (127 - level))
		g_vEnemies.push_back(CEnemy());

	g_pStarField->Update(.02f);

	for (size_t i = 0; i <g_vEnemies.size(); i++)
		g_vEnemies[i].Update(.02f);

	for (size_t i = 0; i < g_vPlayerBullets.size(); i++)
		g_vPlayerBullets[i].Update(.02f);

	for (size_t i = 0; i < g_vEnemyBullets.size(); i++)
		g_vEnemyBullets[i].Update(.02f);


	for (size_t i = 0; i < g_vEnemyBullets.size(); i++)
	{
		if (g_vEnemyBullets[i].TestCollision(*g_pPlayer))
		{
			g_pPlayer->DoDamage(g_vEnemyBullets[i].GetDamage());
			g_vEnemyBullets[i] = *g_vEnemyBullets.rbegin();
			g_vEnemyBullets.pop_back();
		}
	}


	for (size_t i = 0; i < g_vEnemies.size(); i++)
	{
		if (g_vEnemies[i].TestCollision(*g_pPlayer))	//collision with player ship
			g_vEnemies[i].DoDamage(100);

		for (size_t j = 0; j < g_vPlayerBullets.size(); j++)	//collision with player bullets
			if (g_vPlayerBullets[j].TestCollision(g_vEnemies[i]))
			{
				g_vEnemies[i].DoDamage(g_vPlayerBullets[j].GetDamage());
				g_vPlayerBullets[j] = *g_vPlayerBullets.rbegin();
				g_vPlayerBullets.pop_back();
			}

			//out of screen
		if (g_vEnemies[i].GetPos().y>400)
			g_vEnemies[i].DoDamage(100000);


		//is enemy alive?
		if (!g_vEnemies[i].IsAlive())
		{
			g_vEnemies[i] = *g_vEnemies.rbegin();
			g_vEnemies.pop_back();
		}

	}

	
}

void CSystem::Draw()
{
	g_pStarField->Draw();
	g_pPlayer->Draw();

	for (size_t i = 0; i < g_vEnemies.size(); i++)
		g_vEnemies[i].Draw();

	for (size_t i = 0; i < g_vPlayerBullets.size(); i++)
		g_vPlayerBullets[i].Draw();

	for (size_t i = 0; i < g_vEnemyBullets.size(); i++)
		g_vEnemyBullets[i].Draw();
}

void CSystem::DrawSetup()
{
	CGraphics& gr = CGraphics::get();
	if (!FAILED(gr.StartRender(0x00000000)))
	{
		// ����������� ������-������
		gr.SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		gr.SetRenderState(D3DRS_LIGHTING, FALSE);
		gr.SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		gr.SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		gr.SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		gr.SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		gr.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		D3DXMATRIX mat, matViewProj, matProj, matView;
		D3DXMatrixIdentity(&mat);

		// ������� ���� � ��������
		D3DXMatrixTranslation(&matView, 0, 0, 0);
		D3DXMatrixOrthoLH(&matProj, WINDOW_WIDTH, -WINDOW_HEIGHT, 0, 10);

		// �������� ������� ����/��������
		D3DXMatrixMultiply(&matViewProj, &matView, &matProj);

		// ������������� �������
		gr.SetPixelShader(m_pPixelShader);
		gr.SetVertexShader(m_pVertexShader);

		// ������� ��������� � �������
		m_pVertexShader->SetMatrix("mWorld", &mat);
		m_pVertexShader->SetMatrix("mViewProjection", &matViewProj);

		// ����������� ���������� ��������
		gr.SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		gr.SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		gr.SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		// �������� �����-��������
		gr.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		gr.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		gr.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		Draw();

		// ��������� ������
		gr.EndRender();
	}
	else
		gr.Reset();
}
