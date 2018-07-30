#include "stdafx.h"
#include "Minimap.h"
#include "UIImage.h"

Minimap::Minimap()
{
	m_pSprite = NULL;
	m_pMinimap = NULL;
	m_pIcon = NULL;
}


Minimap::~Minimap()
{
	SAFE_RELEASE(m_pMinimap);
	SAFE_RELEASE(m_pIcon);
}

void Minimap::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	
	GetClientRect(g_hWnd, &rc);

	pImage = new UIImage(m_pSprite);
	pImage->SetTexture("resources/ui/map.png");
	pImage->SetPosition(&D3DXVECTOR3(rc.right - 10 - pImage->GetInfo().Width , rc.bottom - 10 - pImage->GetInfo().Height, 0));
	m_pMinimap = pImage;


	pMapIcon = new UIImage(m_pSprite);
	pMapIcon->SetTexture("resources/ui/flat.png");
	m_pIcon = pMapIcon;
	
}

void Minimap::Update()
{
	playerPos = static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition();

	pMapIcon->SetPosition(&D3DXVECTOR3(rc.right - pImage->GetInfo().Width + (playerPos.x / 1300 * pImage->GetInfo().Width + 95),
		(rc.bottom - pImage->GetInfo().Height + (playerPos.z / 660 * pImage->GetInfo().Height) + 94), 0));
	m_pIcon = pMapIcon;

	SAFE_UPDATE(m_pMinimap);
	SAFE_UPDATE(m_pIcon);
}

void Minimap::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	SAFE_RENDER(m_pMinimap);
	SAFE_RENDER(m_pIcon);
	m_pSprite->End();
}