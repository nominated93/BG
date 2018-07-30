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

void Collision::Init(Player * pPlayer, BulletManager * pBM, ItemManager * pIM, Inventory* pInven, ItemBox* pItemBox)
{
	m_pPlayer = pPlayer;
	m_pBM = pBM;
	m_pIM = pIM;
	m_pInven = pInven;
	m_pItemBox = pItemBox;
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
	for (int i = 0; i<m_pIM->GetVecItem().size(); i++)
	{
		if (CheckSphereIntersect(m_pIM->GetVecItem()[i]->GetCollisionSphere().center, m_pIM->GetVecItem()[i]->GetCollisionSphere().radius,
			m_pPlayer->GetCollisionSphere().center, m_pPlayer->GetCollisionSphere().radius))
		{
			if (m_pIM->GetVecItem()[i]->GetIsCollision() == false)
			{
				m_pIM->GetVecItem()[i]->SetIsCollision(true);
				m_pItemBox->m_iVecIndex = i;
				m_pItemBox->AddItemToItemBox(m_pIM->GetVecItem()[i]->GetItemName());
			}
		}

		else
		{
			if (m_pItemBox->GetVecItemBoxIcon().size() > 0 && m_pIM->GetVecItem()[i]->GetIsCollision() == true)
			{
				m_pItemBox->RemoveItemFromItemBox();
			}
			m_pIM->GetVecItem()[i]->SetIsCollision(false);
		}
	}
}

void Collision::Collision_ItemPlayer()
{
	auto vec = m_pIM->GetPVecItem();

	for (int i = 0; i<vec->size(); i++)
	{
		if (CheckSphereIntersect(m_pIM->GetVecItem()[i]->GetCollisionSphere().center, m_pIM->GetVecItem()[i]->GetCollisionSphere().radius,
			m_pPlayer->GetCollisionSphere().center, m_pPlayer->GetCollisionSphere().radius))
		{
			m_pIM->GetVecItem()[i]->SetIsCollision(true);
			m_pInven->AddItemToInven(m_pIM->GetVecItem()[i]->GetItemName());
			vec->erase(vec->begin() + i);


			if (m_pItemBox->GetVecItemBoxIcon().size() > 0)
			{
				m_pItemBox->RemoveItemFromItemBox();
			}
			return;
		}

		else
		{
			m_pIM->GetVecItem()[i]->SetIsCollision(false);

		}
	}
}