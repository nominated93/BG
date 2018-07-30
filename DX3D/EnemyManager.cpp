#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"
#include "BulletManager.h"
#include "Frustum.h"
#include "IMap.h"
#include "OBB.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
	for each(auto p in m_vecEnemy)
	{
		SAFE_DELETE(p);
	}
}



void EnemyManager::Init(Player* player, BulletManager* bulletManager, IMap* map)
{
	m_vecEnemy.resize(MAXENEMY);

	for (int i = 0; i < MAXENEMY; i++)
	{
		m_vecEnemy[i] = new Enemy;
		m_vecEnemy[i]->Init(player, "Character", bulletManager, map);
	}

}

void EnemyManager::Update()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (m_vecEnemy[i]->GetIsAlive() == false) continue;
		m_vecEnemy[i]->Update();
	}
}

void EnemyManager::Render()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		Frustum frustum;
		frustum.Init();
		if (m_vecEnemy[i]->GetIsAlive() == false) continue;
		if (frustum.isIn(&(m_vecEnemy[i]->GetPosition())) == false) continue;
		m_vecEnemy[i]->Render();
	}
}

void EnemyManager::Init()
{
}

void EnemyManager::MakeEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int patternNum)
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (m_vecEnemy[i]->GetIsAlive() == true) continue;
		m_vecEnemy[i]->reMake(pos, dir, patternNum);
		break;
	}
}