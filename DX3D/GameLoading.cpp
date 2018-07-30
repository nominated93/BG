#include "stdafx.h"
#include "GameLoading.h"
#include "UIImage.h"
#include "IUIObject.h"
#include "Loading.h"


GameLoading::GameLoading()
	: m_pSprite(NULL)
	, m_pLoading(NULL)
	, m_time(0)
{
}


GameLoading::~GameLoading()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_DELETE(m_pLoading);
}

void GameLoading::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_pBackGround = new UIImage(m_pSprite);
	m_pBackGround->SetTexture("resources/ui/Loading.png");
	//Root = m_pBackGround;

	//m_pLoadingbar = new UIImage(m_pSprite);
	////m_pLoadingbar->SetTexture("resources/ui/HpBarUp.bmp");
	//m_pLoadingbar->SetTexture("resources/ui/loading.gif");
	//m_pLoadingbar->SetPosition(&D3DXVECTOR3(400, 500, 0));
	//Root->AddChild(loadingbar);

	//UIImage * loading = new UIImage(m_pSprite);
	//loading->SetTexture("resources/ui/HpBarDown.png");
	//loading->SetPosition(&D3DXVECTOR3(300, 720, 0));
	//Root->AddChild(loading);


	m_pLoading = new Loading;
	
	m_pLoading->LoadingSkinnedMesh("Character", "../../", "Character.X");
	m_pLoading->LoadingSkinnedMesh("PlayerAction", "../../", "action.X");
	m_pLoading->LoadingSkinnedMesh("Action", "../../", "action.X");

	m_pLoading->LoadingMesh("AK-47", "resources/weapons", "AK-47.X");
	m_pLoading->LoadingMesh("Head", "resources/weapons", "F_Head_G_01.X");
	m_pLoading->LoadingMesh("Armor", "resources/weapons", "F_Armor_C_01.X");
	m_pLoading->LoadingMesh("Backpack", "resources/weapons", "F_Back_C_01_.X");
}

void GameLoading::Update()
{
	//g_pTimeManager->Update();

	//m_time = (m_pLoading->GetLoadItemSize() / (float)m_pLoading->GetLoadItem().size()) * 600;

	//D3DXIMAGE_INFO info = m_pLoadingbar->GetInfo();
	//info.Width = m_time;
	//m_pLoadingbar->SetInfo(info);
	//m_pLoadingbar->Update();


	m_pLoading->Update();
	if (m_pLoading->LoadingDone())
	{
		g_pSceneManager->SetCurrentScene(SCENE_LOBBY);
		//g_pSceneManager->SetCurrentScene(SCENE_LOBBYLOADING);
	}
}

void GameLoading::Render()
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

void GameLoading::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
