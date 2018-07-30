#include "stdafx.h"
#include "LobbyLoading.h"
#include "UIImage.h"
#include "IUIObject.h"
#include "Loading.h"


LobbyLoading::LobbyLoading()
	: m_pSprite(NULL)
	, m_pLoading(NULL)
	, m_time(0)
{
}


LobbyLoading::~LobbyLoading()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_DELETE(m_pLoading);
}

void LobbyLoading::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_pBackGround = new UIImage(m_pSprite);
	m_pBackGround->SetTexture("resources/ui/lobbyloading.jpg");
	//Root = m_pBackGround;

	m_pLoadingbar = new UIImage(m_pSprite);
	//m_pLoadingbar->SetTexture("resources/ui/HpBarUp.bmp");
	m_pLoadingbar->SetTexture("resources/ui/loading.gif");
	m_pLoadingbar->SetPosition(&D3DXVECTOR3(400, 500, 0));
	//Root->AddChild(loadingbar);

	//UIImage * loading = new UIImage(m_pSprite);
	//loading->SetTexture("resources/ui/HpBarDown.png");
	//loading->SetPosition(&D3DXVECTOR3(300, 720, 0));
	//Root->AddChild(loading);



	//m_pLoading->LoadingSkinnedMesh("Character", "resources/player", "Character.X");
	//m_pLoading->LoadingSkinnedMesh("sky", "resources/player/Block", "sky.X");

	//m_pLoading->LoadingSkinnedMesh("AK-47", "resources/weapons", "AK-47.X");
	//m_pLoading->LoadingSkinnedMesh("Head", "resources/weapons", "F_Head_G_01.X");
	//m_pLoading->LoadingSkinnedMesh("Armor", "resources/weapons", "F_Armor_C_01.X");
	//m_pLoading->LoadingSkinnedMesh("Backpack", "resources/weapons", "F_Back_C_01_.X");
}

bool LobbyLoading::InitScene()
{
	return true;
}

void LobbyLoading::Update()
{
	//g_pTimeManager->Update();

	//m_time = (m_pLoading->GetLoadItemSize() / (float)m_pLoading->GetLoadItem().size()) * 600;

	//D3DXIMAGE_INFO info = m_pBackGround->GetInfo();
	//info.Width = 1300;
	//info.Height	= 660;
	//m_pBackGround->SetInfo(info);
	//m_pBackGround->Update();

	m_pLoading->Update();
	//if (m_pLoading->LoadingDone())
	{
		g_pSceneManager->SetCurrentScene(SCENE_OBJMAP);
	}
}

void LobbyLoading::Render()
{
	g_pDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pDevice->BeginScene();

	m_pBackGround->Render();
	//m_pLoadingbar->Render();

	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

void LobbyLoading::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
