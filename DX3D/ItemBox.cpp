#include "stdafx.h"
#include "ItemBox.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemManager.h"

ItemBox::ItemBox() :
	m_vecItemBoxIcon(NULL),
	m_pInven(NULL)
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

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iterListTemp = m_iterListTemp;

		CItem->GetPNameText()->m_text = _T("AK 47");

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
		CItem->GetPIconImage()->SetTexture("resources/ui/��ź����������.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);
		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iterListTemp = m_iterListTemp;

		CItem->GetPNameText()->m_text = _T("��ź����");

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
		CItem->GetPIconImage()->SetTexture("resources/ui/�Ѳ�������.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);
		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iterListTemp = m_iterListTemp;

		CItem->GetPNameText()->m_text = _T("��ź��");

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
		CItem->GetPIconImage()->SetTexture("resources/ui/���������.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		CItem->m_iterListTemp = m_iterListTemp;

		CItem->GetPNameText()->m_text = _T("����");

		m_vecItemBoxIcon.push_back(CItem);
	}
	break;

	}
}

void ItemBox::RemoveItemFromItemBox_Item()
{
	auto pList = m_pIM->GetPListItem();

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
			pList->erase(m_vecItemBoxIcon[i]->m_iterListTemp);
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

		int iDeltaY = 42;
		for (int j = 0; j < m_vecItemBoxIcon.size(); j++)
		{
			D3DXVECTOR3 vDeltaPos(75, 95, 0);

			vDeltaPos.y = vDeltaPos.y + j * iDeltaY;
			m_vecItemBoxIcon[j]->GetPBGIconImage()->SetPosition(&vDeltaPos);
		}
	
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
