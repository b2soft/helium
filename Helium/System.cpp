#include "Head.h"

CPlayerShip*			g_pPlayer;
CStarField*				g_pStarField;
std::vector<CEnemy>		g_vEnemies;
std::vector<CBullet>	g_vPlayerBullets;
std::vector<CBullet>	g_vEnemyBullets;
std::vector<CExplosion*>	g_vExplosions;
CText*					g_pTest;
CClock*					g_pClock;

int level = 5;
long double g_iPoints = 0;

PCShader m_pPixelShader, m_pVertexShader;
HWND m_hWindow;

void FireEnemy(D3DXVECTOR2 pos, D3DXVECTOR2 speed)
{
	g_vEnemyBullets.push_back(CBullet(pos+D3DXVECTOR2(0, 25), speed, L"Data/bullet-enemy.dds"));
}

void ProcessUserInput(float fDeltaTime)
{
	int dx = 0;
	if (GetAsyncKeyState(VK_LEFT) & 32768)
		dx--; // движемся влево
	if (GetAsyncKeyState(VK_RIGHT) & 32768)
		dx++; // движемся вправо

// 	if (GetAsyncKeyState(VK_UP) & 32768)
// 	{
// 		if (level <= 50)
// 			level++;
// 	}


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
	// Инициализируем графику
	if (!CGraphics::get().Init(hWnd, iWindowWidth, iWindowHeight))
		return FALSE;
	// загружаем вертексный шейдер
	m_pVertexShader = CGraphics::get().LoadShader("Data/vs.hlsl", "main", "vs_3_0");
	// загружаем пиксельный шейдер
	m_pPixelShader = CGraphics::get().LoadShader("Data/ps.hlsl", "pixel_shader_main", "ps_3_0");

	g_pPlayer = new CPlayerShip();
	g_pStarField = new CStarField();
	g_pTest = new CText(D3DXVECTOR2(10.0f, 10.0f), "Text", 30, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return TRUE;
}

void CSystem::Initialize(HINSTANCE hInstance)
{
	m_hWindow = MakeWindow(hInstance);

	InitD3D(m_hWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	g_pClock = new CClock();
	g_pClock->Initialize();
	
	MainLoop();
}

int CSystem::MainLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		g_pClock->Update();
		Update(g_pClock->DT());
		DrawSetup();

		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Release();

	return 1;
}

void CSystem::Update(const float fDeltaTime)
{
	
	if (GetForegroundWindow()==m_hWindow)
		ProcessUserInput(fDeltaTime);

	if ((rand() & (127 - level)) == (127 - level))
		g_vEnemies.push_back(CEnemy());

	g_pStarField->Update(fDeltaTime);

	for_each(g_vEnemies.begin(), g_vEnemies.end(),
		bind2nd(mem_fun_ref(&CEnemy::Update), fDeltaTime));

	for_each(g_vPlayerBullets.begin(), g_vPlayerBullets.end(),
		bind2nd(mem_fun_ref(&CBullet::Update), fDeltaTime));

	for_each(g_vEnemyBullets.begin(), g_vEnemyBullets.end(),
		bind2nd(mem_fun_ref(&CBullet::Update), fDeltaTime));

	for_each(g_vExplosions.begin(), g_vExplosions.end(),
		bind2nd(mem_fun(&CExplosion::Update), fDeltaTime));

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

			if (!g_vEnemies[i].IsAlive())
			{
				CExplosion *pExplosion = new CExplosion(g_vEnemies[i].GetPos());
					g_vExplosions.push_back(pExplosion);
				g_iPoints++;
			}



				//out of screen
		if (g_vEnemies[i].GetPos().y>400)
			g_vEnemies[i].DoDamage(100000);

		if (g_vEnemies.size())
			g_vEnemies.erase(remove_if(g_vEnemies.begin(), g_vEnemies.end(),
			not1(mem_fun_ref(&CEnemy::IsAlive))), g_vEnemies.end());

		for (size_t i = 0; i < g_vExplosions.size(); i++)
		if (g_vExplosions[i]->IsFinished())
		{
			delete g_vExplosions[i];
			g_vExplosions[i] = *g_vExplosions.rbegin();
			g_vExplosions.pop_back();
		}

	}
 	string score = "Score: ";
	score += to_string(g_iPoints);
	g_pTest->Update(score);
	
}

void CSystem::Draw()
{
	g_pStarField->Draw();
	g_pPlayer->Draw();

	for_each(g_vEnemies.begin(), g_vEnemies.end(),
		mem_fun_ref(&CEnemy::Draw));

	for_each(g_vPlayerBullets.begin(), g_vPlayerBullets.end(),
		mem_fun_ref(&CBullet::Draw));

	for_each(g_vEnemyBullets.begin(), g_vEnemyBullets.end(),
		mem_fun_ref(&CBullet::Draw));

	for_each(g_vExplosions.begin(), g_vExplosions.end(),
		mem_fun(&CExplosion::Draw));

	g_pTest->Draw();
}

void CSystem::DrawSetup()
{
	CGraphics& gr = CGraphics::get();
	if (!FAILED(gr.StartRender(0x00000000)))
	{
		// настраиваем рендер-стейты
		gr.SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		gr.SetRenderState(D3DRS_LIGHTING, FALSE);
		gr.SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		gr.SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		gr.SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		gr.SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		gr.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		D3DXMATRIX mat, matViewProj, matProj, matView;
		D3DXMatrixIdentity(&mat);

		// матрицы вида и проекции
		D3DXMatrixTranslation(&matView, 0, 0, 0);
		D3DXMatrixOrthoLH(&matProj, WINDOW_WIDTH, -WINDOW_HEIGHT, 0, 10);

		// получаем матрицу вида/проекции
		D3DXMatrixMultiply(&matViewProj, &matView, &matProj);

		// устанавливаем шейдеры
		gr.SetPixelShader(m_pPixelShader);
		gr.SetVertexShader(m_pVertexShader);

		// передаём константы в шейдеры
		m_pVertexShader->SetMatrix("mWorld", &mat);
		m_pVertexShader->SetMatrix("mViewProjection", &matViewProj);

		// настраиваем фильтрацию текстуры
		gr.SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		gr.SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		gr.SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		// включаем альфа-блендинг
		gr.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		gr.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		gr.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		Draw();

		// закончили рендер
		gr.EndRender();
	}
	else
		gr.Reset();
}

void CSystem::Release()
{
	delete g_pTest;
	delete g_pStarField;
	delete g_pPlayer;
	delete g_pClock;
	
	for (size_t i = 0; i < g_vExplosions.size(); i++)
		delete g_vExplosions[i];
	g_vExplosions.clear();

	g_vEnemyBullets.clear();
	g_vPlayerBullets.clear();
	g_vEnemies.clear();
}
