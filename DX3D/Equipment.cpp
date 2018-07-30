#include "stdafx.h"
#include "Equipment.h"
#include "Item.h"
#include "Inventory.h"

Equipment::Equipment() :
	m_pEquipmentIcon(NULL)
{
}


Equipment::~Equipment() 
{
	SAFE_RELEASE(m_pEquipmentIcon);
}

void Equipment::Init()
{
	m_pEquipmentIcon = new UIImage(m_pSprite);
	m_pEquipmentIcon->SetTexture("resources/ui/UI_PLAYER.png");
	m_pEquipmentIcon->SetPosition(&D3DXVECTOR3(100, 0, 0));
}

void Equipment::Update()
{
	EquipmentItemIconUpdate();
}

void Equipment::Render()
{
	EquipmentItemIconRender();
}

void Equipment::AddItemToEquipment(ITEM_LIST IL)
{
	switch (IL)
	{
	case ITEM_LIST::AK47:
	{
		Item * CItem;
		CItem = new Item;

		CItem->Init();
		CItem->SetItemName(ITEM_LIST::AK47);
		CItem->SetItemInto(ITEM_INTO::EQUIPMENT);
		CItem->GetPIconImage()->SetPosition(&D3DXVECTOR3(870, 70, 0));
		CItem->GetPIconImage()->SetTexture("resources/ui/AK47ICON_EQ.png");
		CItem->GetPIconImage()->m_AlphaBlendValue = 200;

		m_vecEquipmentItemIcon.push_back(CItem);
	}
	break;

	case ITEM_LIST::ARMOR:
	{
		Item * CItem;
		CItem = new Item;

		CItem->Init();
		CItem->SetItemName(ITEM_LIST::ARMOR);
		CItem->SetItemInto(ITEM_INTO::EQUIPMENT);
		CItem->GetPIconImage()->SetPosition(&D3DXVECTOR3(447, 269, 0));
		CItem->GetPIconImage()->SetTexture("resources/ui/¹æÅºÁ¶³¢¾ÆÀÌÄÜ.png");
		CItem->GetPIconImage()->m_AlphaBlendValue = 200;
		m_vecEquipmentItemIcon.push_back(CItem);
	}
	break;

	case ITEM_LIST::HEAD:
	{
		Item * CItem;
		CItem = new Item;

		CItem->Init();
		CItem->SetItemName(ITEM_LIST::HEAD);
		CItem->SetItemInto(ITEM_INTO::EQUIPMENT);
		CItem->GetPIconImage()->SetPosition(&D3DXVECTOR3(447, 108, 0));
		CItem->GetPIconImage()->SetTexture("resources/ui/¶Ñ²±¾ÆÀÌÄÜ.png");
		CItem->GetPIconImage()->m_AlphaBlendValue = 200;

		m_vecEquipmentItemIcon.push_back(CItem);
	}
	break;

	case ITEM_LIST::BACKPACK:
	{
		Item * CItem;
		CItem = new Item;

		CItem->Init();
		CItem->SetItemName(ITEM_LIST::BACKPACK);
		CItem->SetItemInto(ITEM_INTO::EQUIPMENT);
		CItem->GetPIconImage()->SetPosition(&D3DXVECTOR3(447, 228, 0));
		CItem->GetPIconImage()->SetTexture("resources/ui/°¡¹æ¾ÆÀÌÄÜ.png");
		CItem->GetPIconImage()->m_AlphaBlendValue = 200;

		m_vecEquipmentItemIcon.push_back(CItem);
	}
	break;

	}
}

void Equipment::EquipmentItemIconUpdate()
{
	if (m_vecEquipmentItemIcon.size()>0)
	{
		for (int i = 0; i<m_vecEquipmentItemIcon.size(); i++)
		{
			m_vecEquipmentItemIcon[i]->GetPIconImage()->Update();
		}
	}
}

void Equipment::EquipmentItemIconRender()
{
	if (m_vecEquipmentItemIcon.size()>0)
	{
		for (int i = 0; i<m_vecEquipmentItemIcon.size(); i++)
		{
			m_vecEquipmentItemIcon[i]->GetPIconImage()->Render();
		}
	}
}

void Equipment::RemoveItemFromEquipment()
{
	for (int i = 0; i<m_vecEquipmentItemIcon.size();)
	{
		LPD3DXSPRITE pSprite;
		D3DXCreateSprite(g_pDevice, &pSprite);

		D3DXMATRIXA16 mat;

		pSprite->GetTransform(&mat);

		int left = mat._41 + m_vecEquipmentItemIcon[i]->GetPIconImage()->GetCombinedPosition().x;
		int top = mat._42 + m_vecEquipmentItemIcon[i]->GetPIconImage()->GetCombinedPosition().y;
		int right = left + m_vecEquipmentItemIcon[i]->GetPIconImage()->GetInfo().Width;
		int bottom = top + m_vecEquipmentItemIcon[i]->GetPIconImage()->GetInfo().Height;

		RECT rc;
		SetRect(&rc, left, top, right, bottom);

		POINT mousePoint;
		GetCursorPos(&mousePoint);
		ScreenToClient(g_hWnd, &mousePoint);

		if (PtInRect(&rc, mousePoint))
		{
			m_pIeven->AddItemToInven(m_vecEquipmentItemIcon[i]->GetItemName());
			m_vecEquipmentItemIcon.erase(m_vecEquipmentItemIcon.begin() + i);
		}

		else
		{
			i++;
		}
	}
}
