#include "stdafx.h"
#include "Collision.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Item.h"
#include "ItemBox.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::Init()
{
}

void Collision::Init(Player * pPlayer, BulletManager * pBM, ItemManager * pIM)
{
	m_pPlayer = pPlayer;
	m_pBM = pBM;
	m_pIM = pIM;
	m_pInven = pPlayer->GetPInven();
	m_pItemBox = pPlayer->GetPInven()->GetPItemBox();
}

void Collision::Update()
{
	if (g_pKeyboardManager->isOnceKeyDown('F'))
	{
		Collision_ItemPlayer();
	}

	//if(g_pKeyboardManager)
	Collision_ItemBoxPlayer();
}

void Collision::Render()
{
}

bool Collision::CheckSphereIntersect(D3DXVECTOR3 vCenter1, float fRadius1, D3DXVECTOR3 vCenter2, float fRadius2)
{
	float fDistance;
	D3DXVECTOR3 vDiff;
	vDiff = (vCenter2 / 0.05f) - (vCenter1 / 0.05f);   //리소스 크기를 0.04만큼 줄여줘서 계산법에서 나눈다
	fDistance = D3DXVec3Length(&vDiff);
	if (fDistance <= (fRadius1 + fRadius2))
		return true;

	return false;
}

void Collision::Collision_ItemBoxPlayer()
{
	auto pList = m_pIM->GetPListItem();
	list<Item*>::iterator iterListItem;
	for (iterListItem = pList->begin(); iterListItem!= pList->end(); iterListItem++)
	{
		if (CheckSphereIntersect((*iterListItem)->GetCollisionSphere().center, (*iterListItem)->GetCollisionSphere().radius,
			m_pPlayer->GetCollisionSphere().center, m_pPlayer->GetCollisionSphere().radius))
		{
			if ((*iterListItem)->GetIsCollision() == false)
			{
				(*iterListItem)->SetIsCollision(true);
				m_pItemBox->m_iterListTemp = iterListItem;
				m_pItemBox->AddItemToItemBox((*iterListItem)->GetItemName());
			}
		}

		else
		{
			if (m_pItemBox->GetVecItemBoxIcon().size() > 0 && (*iterListItem)->GetIsCollision() == true)
			{
				m_pItemBox->RemoveItemFromItemBox();
			}
			(*iterListItem)->SetIsCollision(false);
		}
	}
}

void Collision::Collision_ItemPlayer()
{
	auto pList = m_pIM->GetPListItem();
	list<Item*>::iterator iterListItem;
	for (iterListItem = pList->begin(); iterListItem != pList->end(); iterListItem++)
	{
		if (CheckSphereIntersect((*iterListItem)->GetCollisionSphere().center, (*iterListItem)->GetCollisionSphere().radius,
			m_pPlayer->GetCollisionSphere().center, m_pPlayer->GetCollisionSphere().radius))
		{
			(*iterListItem)->SetIsCollision(true);
			m_pInven->AddItemToInven((*iterListItem)->GetItemName());
			pList->erase(iterListItem);


			if (m_pItemBox->GetVecItemBoxIcon().size() > 0)
			{
				m_pItemBox->RemoveItemFromItemBox();
			}
			return;
		}

		else
		{
			(*iterListItem)->SetIsCollision(false);

		}
	}
}