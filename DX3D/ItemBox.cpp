#include "stdafx.h"
#include "ItemBox.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemManager.h"

ItemBox::ItemBox() :
	m_vecItemBoxIcon(NULL),
	m_pInven(NULL),
	m_iVecIndex(0)

{
}


ItemBox::~ItemBox()
{
	m_vecItemBoxIcon.clear();
	m_pInven = NULL;
}

void ItemBox::Init()
{
}

void ItemBox::Update()
{
	ItemBoxIconUpdate();
}

void ItemBox::Render()
{
	ItemBoxIconRender();
}

void ItemBox::AddItemToItemBox(ITEM_LIST IL)
{
	D3DXVECTOR3 vDeltaPos(75, 95, 0);
	int iDeltaY = 42;

	if (m_vecItemBoxIcon.size())
	{
		vDeltaPos.y = vDeltaPos.y + m_vecItemBoxIcon.size()* iDeltaY;
	}

	switch (IL)
	{
	case ITEM_LIST::AK47:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::AK47);
		CItem->SetItemInto(ITEM_INTO::ITEMBOX);
		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/AK47ICON_INVEN.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iVecIndex = m_iVecIndex;

		m_vecItemBoxIcon.push_back(CItem);
	}
	break;

	case ITEM_LIST::ARMOR:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::ARMOR);
		CItem->SetItemInto(ITEM_INTO::ITEMBOX);
		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/¹æÅºÁ¶³¢¾ÆÀÌÄÜ.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iVecIndex = m_iVecIndex;

		m_vecItemBoxIcon.push_back(CItem);
	}
	break;

	case ITEM_LIST::HEAD:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::HEAD);
		CItem->SetItemInto(ITEM_INTO::ITEMBOX);
		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/¶Ñ²±¾ÆÀÌÄÜ.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iVecIndex = m_iVecIndex;

		m_vecItemBoxIcon.push_back(CItem);
	}
	break;

	case ITEM_LIST::BACKPACK:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::BACKPACK);
		CItem->SetItemInto(ITEM_INTO::ITEMBOX);
		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/°¡¹æ¾ÆÀÌÄÜ.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iVecIndex = m_iVecIndex;

		m_vecItemBoxIcon.push_back(CItem);
	}
	break;

	}
}

void ItemBox::RemoveItemFromItemBox_Item()
{
	auto pVec = m_pIM->GetPVecItem();

	for (int i = 0; i<m_vecItemBoxIcon.size();)
	{
		LPD3DXSPRITE pSprite;
		D3DXCreateSprite(g_pDevice, &pSprite);

		D3DXMATRIXA16 mat;
		pSprite->GetTransform(&mat);

		int left = mat._41 + m_vecItemBoxIcon[i]->GetPIconImage()->GetCombinedPosition().x;
		int top = mat._42 + m_vecItemBoxIcon[i]->GetPIconImage()->GetCombinedPosition().y;
		int right = left + m_vecItemBoxIcon[i]->GetPIconImage()->GetInfo().Width;
		int bottom = top + m_vecItemBoxIcon[i]->GetPIconImage()->GetInfo().Height;

		RECT rc;
		SetRect(&rc, left, top, right, bottom);

		POINT mousePoint;
		GetCursorPos(&mousePoint);
		ScreenToClient(g_hWnd, &mousePoint);

		if (PtInRect(&rc, mousePoint))
		{
			pVec->erase(pVec->begin()+ m_vecItemBoxIcon[i]->m_iVecIndex);
			int iDeltaY = 42;

			m_vecItemBoxIcon[i]->m_pRootIcon->RemoveChild(0);
			m_pInven->AddItemToInven(m_vecItemBoxIcon[i]->GetItemName());
			m_vecItemBoxIcon.erase(m_vecItemBoxIcon.begin() + i);

			for (int j = 0; j < m_vecItemBoxIcon.size(); j++)
			{
				D3DXVECTOR3 vDeltaPos(75, 95, 0);

				vDeltaPos.y = vDeltaPos.y + j * iDeltaY;
				m_vecItemBoxIcon[j]->GetPBGIconImage()->SetPosition(&vDeltaPos);
			}
		}
		else
		{
			i++;
		}
	}
	
}

void ItemBox::RemoveItemFromItemBox()
{
	for (int i = 0;i<m_vecItemBoxIcon.size();i++)
	{
		m_vecItemBoxIcon[i]->m_pRootIcon->RemoveChild(0);
		m_vecItemBoxIcon.erase(m_vecItemBoxIcon.begin()+i);
	}
}

void ItemBox::ItemBoxIconUpdate()
{
	if (m_vecItemBoxIcon.size() > 0)
	{
		for (int i = 0; i<m_vecItemBoxIcon.size(); i++)
		{
			m_vecItemBoxIcon[i]->IconUpdate();
		}
	}
}

void ItemBox::ItemBoxIconRender()
{
	if (m_vecItemBoxIcon.size() > 0)
	{
		for (int i = 0; i<m_vecItemBoxIcon.size(); i++)
		{
			m_vecItemBoxIcon[i]->IconRender();
		}
	}
}
