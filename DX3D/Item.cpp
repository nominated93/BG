#include "stdafx.h"
#include "Item.h"
#include "SkinnedMesh.h"
#include "UIImage.h"

Item::Item() :
	m_pSkinnedMesh(NULL),
	m_pIconImage(NULL),
	m_pIconBackGroundImage(NULL),
	m_isCollision(false),
	m_eMouseState(NORMAL),
	m_isPick(false),
	m_pRootIcon(NULL)
{
}

Item::~Item()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pIconImage);
	SAFE_DELETE(m_pIconBackGroundImage);
	SAFE_DELETE_ARRAY(m_pRootIcon);
}


void Item::Init()
{
	//m_pSkinnedMesh = new SkinnedMesh();
	m_pIconImage = new UIImage(m_pSprite);
	m_pIconBackGroundImage = new UIImage(m_pSprite);

}

void Item::Update()
{
	m_tCollisionSphere.center = m_pos;
}

void Item::Render()
{
	D3DXMATRIXA16 matS, matR, matT, matWorld;

	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixIdentity(&matT);

	//m_baseRotY = g_pCamera->m_rotY;

	D3DXMatrixRotationY(&matR, m_rot.y);
	D3DXMatrixRotationX(&matR, D3DX_PI/2);

	//Debug->AddText(m_rot.y);
	//D3DXVec3TransformNormal(&m_rot, &m_rot, &matR);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	//D3DXMatrixIdentity(&matS);

	matWorld = matS * matR * matT;

	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pSkinnedMesh->Render(NULL, &matWorld);
	m_pMesh->DrawSubset(0);
	Debug->AddText("isC : ");
	Debug->AddText(m_isCollision);
	Debug->EndLine();
}

void Item::Setup(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL, ITEM_INTO II)
{
	m_pSkinnedMesh = new SkinnedMesh();
	m_pIconImage = new UIImage(m_pSprite);

	switch (IL)
	{
	case ITEM_LIST::AK47:
		m_pos = pos;
		m_rot = rot;
		m_pSkinnedMesh->Setup("resources/weapons", "AK-47.X");
		m_tItemName = IL;
		m_tItemInto = II;

		m_tCollisionSphere.center = m_pos;
		m_tCollisionSphere.radius = 20;
		D3DXCreateSphere(g_pDevice, m_tCollisionSphere.radius, 10, 10, &m_pMesh, NULL);
		break;
	case ITEM_LIST::ARMOR:
		m_pos = pos;
		m_rot = rot;
		m_pSkinnedMesh->Setup("resources/weapons", "F_Armor_C_01.X");
		m_tItemName = IL;
		m_tItemInto = II;

		m_tCollisionSphere.center = m_pos;
		m_tCollisionSphere.radius = 20;
		D3DXCreateSphere(g_pDevice, m_tCollisionSphere.radius, 10, 10, &m_pMesh, NULL);
		break;
	case ITEM_LIST::BACKPACK:
		m_pos = pos;
		m_rot = rot;
		m_pSkinnedMesh->Setup("resources/weapons", "F_Back_C_01_.X");
		m_tItemName = IL;
		m_tItemInto = II;

		m_fFixRenderZ = 10.f;
		m_tCollisionSphere.center = m_pos;
		m_tCollisionSphere.radius = 20;
		D3DXCreateSphere(g_pDevice, m_tCollisionSphere.radius, 10, 10, &m_pMesh, NULL);
		break;
	case ITEM_LIST::HEAD:
		m_pos = pos;
		m_rot = rot;
		m_pSkinnedMesh->Setup("resources/weapons", "F_Head_G_01.X");
		m_tItemName = IL;
		m_tItemInto = II;

		m_tCollisionSphere.center = m_pos;
		m_tCollisionSphere.radius = 20;
		D3DXCreateSphere(g_pDevice, m_tCollisionSphere.radius, 10, 10, &m_pMesh, NULL);
		break;
	case ITEM_LIST::END:
		break;
	default:
		break;
	}

}

void Item::MouseDrag(bool isClick)
{
	LPD3DXSPRITE pSprite;
	D3DXCreateSprite(g_pDevice, &pSprite);

	D3DXMATRIXA16 mat;
	pSprite->GetTransform(&mat);

	int left = mat._41 + m_pIconBackGroundImage->GetCombinedPosition().x;
	int top = mat._42 + m_pIconBackGroundImage->GetCombinedPosition().y;
	int right = left + m_pIconBackGroundImage->GetInfo().Width;
	int bottom = top + m_pIconBackGroundImage->GetInfo().Height;

	RECT rect;
	SetRect(&rect, left, top, right, bottom);

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);


	static D3DXVECTOR3 vStartPos;

	Debug->AddText("0 normal   1 over   2 seleted   3 seletedmove  : ");
	Debug->AddText(m_eMouseState);

	Debug->EndLine();

	//마우스 포인터가 영역 안에 있을 때

	if (!isClick || m_isPick)
	{
		if (PtInRect(&rect, ptMouse))
		{
			if (m_eMouseState == MOUSEOVER && (g_pKeyboardManager->isOnceKeyDown(VK_LBUTTON)))
			{
				vStartPos = m_pIconBackGroundImage->GetPosition();
				m_isPick = true;
			}

			if (m_eMouseState == SELECTEDMOVE && (g_pKeyboardManager->isOnceKeyUp(VK_LBUTTON)))
			{
				m_pIconBackGroundImage->SetPosition(&vStartPos);
				m_isPick = false;
				m_eMouseState = NORMAL;
			}

			if (g_pKeyboardManager->isStayKeyDown(VK_LBUTTON))
			{
				m_eMouseState = SELECTEDMOVE;
				m_pIconBackGroundImage->SetPosition(&D3DXVECTOR3(ptMouse.x - 40, ptMouse.y - 8, 0));
			}

			else
			{
				m_eMouseState = MOUSEOVER;
			}
		}
		else
		{
			if (m_eMouseState == SELECTEDMOVE && g_pKeyboardManager->isStayKeyDown(VK_LBUTTON))
			{
				m_pIconBackGroundImage->SetPosition(&D3DXVECTOR3(ptMouse.x - 40, ptMouse.y - 8, 0));
			}
			else
			{
				m_eMouseState = NORMAL;
			}
		}
	}


	if (m_eMouseState == MOUSEOVER)
	{
		m_pIconBackGroundImage->m_AlphaBlendValue = 30;
	}
	else if (m_eMouseState == NORMAL)
	{
		m_pIconBackGroundImage->m_AlphaBlendValue = 15;
	}

}

void Item::IconUpdate()
{
	SAFE_UPDATE(m_pRootIcon)
}

void Item::IconRender()
{
	SAFE_RENDER(m_pRootIcon)
}
