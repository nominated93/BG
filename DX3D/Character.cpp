#include "stdafx.h"
#include "Character.h"
#include "SkinnedMesh.h"

#include "IUIObject.h"
#include "UIImage.h"
#include "SkyBox.h"


Character::Character()
	: m_pSkinnedMesh(NULL)
{
}


Character::~Character()
{
	SAFE_RELEASE(m_pSkinnedMesh);
}

void Character::Init()
{
	//m_pos = D3DXVECTOR3(1, 50, 1);
	//g_pCamera->SetTarget(&m_pos);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_pBackGround = new UIImage(m_pSprite);
	m_pBackGround->SetTexture("resources/ui/lobby2.jpg");
	m_pBackGround->SetPosition(&D3DXVECTOR3(0, 0, -100));
	m_pBackGround->Update();

	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Character");
	m_pSkinnedMesh->SetAnimationIndex(Melee_stand_idle);
}

void Character::Update()
{
	m_pSkinnedMesh->Update();
}

void Character::Render()
{
	//D3DVIEWPORT9 viewPort;
	//viewPort.X = 0;
	//viewPort.Y = 0;
	//viewPort.Width = WINSIZEX;
	//viewPort.Height = WINSIZEY;
	//g_pDevice->SetViewport(&viewPort);

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMATRIXA16 matS, matT, matRY;
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&matRY, D3DX_PI);
	D3DXMatrixTranslation(&matT, 0, -20, 0);
	m_matWorld = matS * matRY * matT;


	D3DXMATRIXA16 matView, matProj;

	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.f, 0.f, -10.f), &D3DXVECTOR3(0.f, 4.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f));
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.f, WINSIZEX / (float)WINSIZEY, 1.f, 1000.f);

	g_pDevice->SetTransform(D3DTS_VIEW, &matView);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	m_pSkinnedMesh->Render(NULL);


	D3DXVECTOR3 dir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}
