#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Camera.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "OBB.h"
#include "IMap.h"


BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
	m_vecBullet.clear();
}

void BulletManager::Init()
{
}

void BulletManager::Setup(Player * player, EnemyManager * enemyManager, IMap * map)
{
	m_pPlayer = player;
	m_pEnemyManager = enemyManager;
	m_pObjMap = map;
}

void BulletManager::Update()
{
	for (m_iterBullet = m_vecBullet.begin(); m_iterBullet != m_vecBullet.end(); m_iterBullet++)
	{
		D3DXVECTOR3 tempPos;
		//tempPos = (*m_iterBullet)->GetPosition() + (*m_iterBullet)->GetSpeed() * (*m_iterBullet)->GetRotation();
		tempPos = (*m_iterBullet)->GetPosition();

		//진행경로를 향하는 obb 하나를 만들어줌
		OBB tempOBB;
		tempOBB.Init(tempPos, (*m_iterBullet)->GetPosition());

		D3DXMATRIXA16 tempMat;
		D3DXMatrixIdentity(&tempMat);
		tempOBB.Update(&tempMat);

		//if ((*m_iterBullet)->GetisAlive() == false) continue;

		if (m_pEnemyManager)
		{
			for (int j = 0; j < m_pEnemyManager->GetvecEnemy().size(); j++)
			{
				if (OBB::IsCollision(m_pEnemyManager->GetvecEnemy()[j]->GetObb(), &tempOBB))
				{
					m_pEnemyManager->GetvecEnemy()[j]->BulletHit(30);
			/*		if (m_pEnemyManager->GetvecEnemy()[j]->GetIsAlive() == false)
					{

						m_pEnemyManager->GetvecEnemy()[j]->BulletHit(30);
					}
					else
					{
						break;
					}
					*/

				}
			}


		}

		//플레이어 충돌
		if (m_pPlayer)
		{
			if (OBB::IsCollision(m_pPlayer->GetOBB(), &tempOBB))
			{
			/*	OBB tempPtoE;
				tempPtoE.Init((*m_iterBullet)->GetPosition(), m_pPlayer->GetPosition() + D3DXVECTOR3(0, 1.0f, 0));
				tempPtoE.Update(&tempMat);*/
				m_pPlayer->BulletHit();
				//(*m_iterBullet)->SetisAlive(false);
			}
		}

		//if ((*m_iterBullet)->GetisAlive() == false) continue;

		(*m_iterBullet)->Update();
	}

	Remove();
}

void BulletManager::Render()
{
	for (m_iterBullet = m_vecBullet.begin(); m_iterBullet != m_vecBullet.end(); m_iterBullet++)
	{
		(*m_iterBullet)->Render();
	}
}

void BulletManager::Fire(float damage, float speed, float range, D3DXVECTOR3* pos, D3DXVECTOR3* dir)
{
	Bullet* bullet;
	bullet = new Bullet;
	bullet->Init(damage, speed, range, pos, dir);

	m_vecBullet.push_back(bullet);
}

void BulletManager::Remove()
{
	float fRange = 50.f;
	for (m_iterBullet = m_vecBullet.begin(); m_iterBullet != m_vecBullet.end(); )
	{
		D3DXVECTOR3 vDiff = (*m_iterBullet)->GetStartPosition() - (*m_iterBullet)->GetPosition();
		float fDistance = D3DXVec3Length(&vDiff);

		if (fDistance >= fRange)
		{
			m_iterBullet = m_vecBullet.erase(m_iterBullet);
		}
		else
			m_iterBullet++;
	}
}