#include "stdafx.h"
#include "Inventory.h"
#include "Equipment.h"
#include "ItemBox.h"
#include "Cursor.h"
#include "Item.h"

Inventory::Inventory():
	m_pInvenUI(NULL),
	m_pEquipment(NULL),
	m_pCursor(NULL),
	m_pRootUI(NULL),
	m_isInvenUI(false)
{
}

Inventory::~Inventory()
{
	SAFE_RELEASE(m_pInvenUI);
	SAFE_RELEASE(m_pEquipment);
	SAFE_RELEASE(m_pCursor);
	
	m_vecInvenItemIcon.clear();
}

void Inventory::Init()
{
	m_pEquipment = new Equipment; m_pEquipment->AddressLink(this); m_pEquipment->Init();
	m_pItemBox = new ItemBox;  m_pItemBox->AddressLink(m_pIM, this); m_pItemBox->Init();
	m_pCursor = new Cursor; m_pCursor->Init();

	m_pInvenUI = new UIImage(m_pSprite);
	m_pInvenUI->SetTexture("resources/ui/inven.bmp");
	m_pRootUI = m_pInvenUI;
	m_pInvenUI->SetPosition(&D3DXVECTOR3(0, 0, 0));
}

void Inventory::Update()
{
	//인벤창 띄우기
	if (g_pKeyboardManager->isOnceKeyDown('I'))
	{
		g_pCamera->SetIsAngleMove(!(g_pCamera->GetIsAngleMove()));
		m_isInvenUI = !m_isInvenUI;
	}

	if (m_isInvenUI)
	{
		if (g_pKeyboardManager->isOnceKeyDown(VK_ESCAPE))
		{
			m_isInvenUI = false;
		}
		SAFE_UPDATE(m_pRootUI);
		m_pEquipment->Update();
		m_pItemBox->Update();
		ItemIconImageUpdate();
		m_pCursor->Update();

	
		if (g_pKeyboardManager->isOnceKeyDown(VK_RBUTTON))
		{

			RemoveItemFromInven();
			m_pEquipment->RemoveItemFromEquipment();
			m_pItemBox->RemoveItemFromItemBox_Item();
		}

		//인벤창에 아이템이 하나라도 있을때
		if (m_vecInvenItemIcon.size() > 0)
		{
			Drag();
		}
	}

	SetIsEquipFromPlayer();
}

void Inventory::Render()
{
	if (m_isInvenUI)
	{
		SAFE_RENDER(m_pRootUI);
		m_pEquipment->Render();
		m_pItemBox->Render();
		ItemIconImageRender();
		m_pCursor->Render();
	}
}

void Inventory::OnClick(UIButton * pSender)
{
}

void Inventory::AddItemToInven(ITEM_LIST IL)
{
	D3DXVECTOR3 vDeltaPos(250, 95, 0);
	int iDeltaY = 42;
		
	if (m_vecInvenItemIcon.size())
	{
		vDeltaPos.y = vDeltaPos.y + m_vecInvenItemIcon.size()* iDeltaY;
	}

	switch (IL)
	{
	case ITEM_LIST::AK47:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::AK47);
		CItem->SetItemInto(ITEM_INTO::INVEN);

		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/AK47ICON_INVEN.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		m_vecInvenItemIcon.push_back(CItem);
	}
		break;

	case ITEM_LIST::ARMOR:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::ARMOR);
		CItem->SetItemInto(ITEM_INTO::INVEN);
		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/방탄조끼아이콘.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		m_vecInvenItemIcon.push_back(CItem);
	}
		break;

	case ITEM_LIST::HEAD:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::HEAD);
		CItem->SetItemInto(ITEM_INTO::INVEN);
		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/뚜껑아이콘.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		m_vecInvenItemIcon.push_back(CItem);
	}
	break;

	case ITEM_LIST::BACKPACK:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->SetItemName(ITEM_LIST::BACKPACK);
		CItem->SetItemInto(ITEM_INTO::INVEN);
		CItem->GetPBGIconImage()->SetTexture("resources/ui/Itembase.bmp");
		CItem->GetPIconImage()->SetTexture("resources/ui/가방아이콘.png");
		CItem->GetPBGIconImage()->SetPosition(&vDeltaPos);

		CItem->m_pRootIcon = CItem->GetPBGIconImage();
		CItem->m_pRootIcon->AddChild(CItem->GetPIconImage());

		CItem->GetPBGIconImage()->m_AlphaBlendValue = 15;

		m_vecInvenItemIcon.push_back(CItem);
	}
	break;

	}
}

void Inventory::RemoveItemFromInven()
{
	for (int i = 0; i<m_vecInvenItemIcon.size(); )
	{
		LPD3DXSPRITE pSprite;
		D3DXCreateSprite(g_pDevice, &pSprite);

		D3DXMATRIXA16 mat;

		pSprite->GetTransform(&mat);

		int left = mat._41 + m_vecInvenItemIcon[i]->GetPIconImage()->GetCombinedPosition().x;
		int top = mat._42 + m_vecInvenItemIcon[i]->GetPIconImage()->GetCombinedPosition().y;
		int right = left + m_vecInvenItemIcon[i]->GetPIconImage()->GetInfo().Width;
		int bottom = top + m_vecInvenItemIcon[i]->GetPIconImage()->GetInfo().Height;

		RECT rc;
		SetRect(&rc, left, top, right, bottom);

		POINT mousePoint;
		GetCursorPos(&mousePoint);
		ScreenToClient(g_hWnd, &mousePoint);

		if (PtInRect(&rc, mousePoint))
		{
			m_vecInvenItemIcon[i]->m_pRootIcon->RemoveChild(0);
			m_pEquipment->SetTrueItemIcon(m_vecInvenItemIcon[i]->GetItemName());
			m_vecInvenItemIcon.erase(m_vecInvenItemIcon.begin() + i);

			int iDeltaY = 42;
			for (int j = 0; j < m_vecInvenItemIcon.size(); j++)
			{
				D3DXVECTOR3 vDeltaPos(250, 95, 0);

				vDeltaPos.y = vDeltaPos.y + j * iDeltaY;
				m_vecInvenItemIcon[j]->GetPBGIconImage()->SetPosition(&vDeltaPos);
			}
		}
		else
		{
			i++;
		}
	}
}

void Inventory::ItemIconImageUpdate()
{
	if (m_vecInvenItemIcon.size() > 0)
	{
		for (int i = 0; i<m_vecInvenItemIcon.size(); i++)
		{
			m_vecInvenItemIcon[i]->IconUpdate();
		}
	}
}

void Inventory::ItemIconImageRender()
{
	if (m_vecInvenItemIcon.size() > 0)
	{
		for (int i = 0; i<m_vecInvenItemIcon.size(); i++)
		{
			m_vecInvenItemIcon[i]->IconRender();
		}
	}
}

void Inventory::Drag()
{
	if (m_vecInvenItemIcon.size() > 0)
	{
		for (int i = 0; i<m_vecInvenItemIcon.size(); i++)
		{
			m_vecInvenItemIcon[i]->MouseDrag(m_pCursor->m_isClick);
		}
	}
}


void Inventory::SetIsEquipFromPlayer()
{
	for (int i = 0; i < m_pEquipment->GetVecEquipmentItemIcon().size(); i++)
	{
		if (m_pEquipment->GetVecEquipmentItemIcon()[i]->GetItemName() == ITEM_LIST::AK47)
		{
			m_isGun = true;
		}

		else if (m_pEquipment->GetVecEquipmentItemIcon()[i]->GetItemName() == ITEM_LIST::BACKPACK)
		{
			m_isBackpack = true;
		}

		else if (m_pEquipment->GetVecEquipmentItemIcon()[i]->GetItemName() == ITEM_LIST::HEAD)
		{
			m_isArmor = true;
		}

		else if (m_pEquipment->GetVecEquipmentItemIcon()[i]->GetItemName() == ITEM_LIST::ARMOR)
		{
			m_isHead = true;
		}
	}
}

