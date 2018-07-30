#include "stdafx.h"
#include "LobbyScene.h"
#include "IUIObject.h"
#include "UIText.h"
#include "UIImage.h"
#include "Cursor.h"
#include "Character.h"
#include "Background.h"

LobbyScene::LobbyScene()
	: m_pSprite(NULL)
	, m_root(NULL)
	, isclick(false)
	, m_pCursor(NULL)
	, m_pCharacter(NULL)
	, m_pBG(NULL)
{
}


LobbyScene::~LobbyScene()
{
	SAFE_DELETE(m_pBG);
	SAFE_RELEASE(m_pCharacter);
	SAFE_RELEASE(m_pSprite);
	SAFE_DELETE(m_root);
	SAFE_DELETE(m_pCursor);
	SAFE_RELEASE(m_BGImage);
}

void LobbyScene::Init()
{

	m_pBG = new Background("resources/ui/lobby2.jpg",
		"resources/ui/lobby2.jpg",
		"resources/ui/lobby2.jpg",
		"resources/ui/lobby2.jpg",
		"resources/ui/lobby2.jpg",
		"resources/ui/lobby2.jpg");

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_pCharacter = new Character; m_pCharacter->Init(); 

	//m_pBackGround = new UIImage(m_pSprite);
	//m_pBackGround->SetTexture("resources/ui/lobby2.jpg");
	//m_pBackGround->SetPosition(&D3DXVECTOR3(0,0,0));
	//m_pBackGround->Update();

	////
	setDevice(g_pDevice);
	setBGImage("resources/ui/lobby2.jpg");
	////
	
	m_pCursor = new Cursor; m_pCursor->Init();
}

void LobbyScene::Update()
{
	RECT rc, WinRECT;
	GetClientRect(g_hWnd, &rc);

	POINT ptMouse;
	GetClientRect(g_hWnd, &WinRECT);
	GetCursorPos(&ptMouse);

	//m_pCharacter->Update();
	//m_pBackGround->Update();
	OnUpdateIScene();
	m_pCursor->Update();

	if (g_pKeyboardManager->isOnceKeyDown(VK_LBUTTON))
	{
		//if (PtInRect(&rc, ptMouse))
		{
			isclick = true;
		}
	}
	if (isclick)
	{
		g_pSceneManager->SetCurrentScene(SCENE_LOBBYLOADING);
		isclick = false;
	}
}

void LobbyScene::Render()
{
	g_pDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pDevice->BeginScene();
	//==============================================

	//m_pBackGround->Render();
	//m_pCharacter->Render();
	//Draw();

	m_pBG->Render();
	m_pCharacter->Render();
	//OnRenderIScene();
	m_pCursor->Render();

	//==============================================
	g_pDevice->EndScene();

	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

void LobbyScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void LobbyScene::setDevice(IDirect3DDevice9* device)
{
	m_Device = device;
	D3DXCreateSprite(m_Device, &m_Sprite);
}

void LobbyScene::setBGImage(std::string path)
{
	D3DXCreateTextureFromFileA(m_Device, path.c_str(), &m_BGImage);
}

void LobbyScene::Draw()
{

	m_Sprite->Begin(0);
	m_Sprite->Draw(m_BGImage, 0, &D3DXVECTOR3(256.0f, 256.0f, 0.0f), 0, D3DCOLOR_XRGB(255, 255, 255));
	m_Sprite->Flush();
	m_Sprite->End();
}

void LobbyScene::onLostDevice()
{
	m_Sprite->OnLostDevice();
}

void LobbyScene::onResetDevice()
{
	m_Sprite->OnResetDevice();

	m_Device->SetRenderState(D3DRS_ALPHAREF, 10);
	m_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_Device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
}