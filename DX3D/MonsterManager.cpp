#include "stdafx.h"
#include "MonsterManager.h"
#include "Monster.h"



MonsterManager::MonsterManager()
{
}


MonsterManager::~MonsterManager()
{
	m_vecMonster.clear();
}

void MonsterManager::Init()
{

	MonsterSetup("zealot.X", D3DXVECTOR3(16, 0, 0), D3DXVECTOR3(0, 0, 1));
	MonsterSetup("zealot.X", D3DXVECTOR3(4, 0, 0), D3DXVECTOR3(0, 0, 1));
	MonsterSetup("zealot.X", D3DXVECTOR3(12, 0, -99), D3DXVECTOR3(0, 0, 1));
	MonsterSetup("zealot.X", D3DXVECTOR3(19, 0, -15), D3DXVECTOR3(0, 0, 1));
	//MonsterSetup("SteveJobs.X", D3DXVECTOR3(11, 0, 10), D3DXVECTOR3(0, 0, 1));
}

void MonsterManager::Update()
{
	for (auto& sprEnemy : m_vecMonster)
	{
		float a;
		D3DXVECTOR3 playerPos = (static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition());

		/*Debug->AddText("플레이어 좌표: ");
		Debug->AddText(playerPos);
		Debug->EndLine();*/

		// 추격 스피드
		float speed = 0.5f;
		// 적 위치 구하기
		D3DXVECTOR3 enemyPos = sprEnemy->GetPosition();
		// 플레이어 위치에서 적 위치를 빼서
		// 플레이어로 향하는 벡터 구하기
		D3DXVECTOR3 direction = playerPos - enemyPos;
		D3DXVECTOR3 direction2 = playerPos - enemyPos;
		direction2.y = .0f;

		// 방향벡터 정규화
		D3DXVec3Normalize(&direction, &direction);
		a = D3DXVec3Length(&direction2);


		Debug->AddText("벡터 길이: ");
		Debug->AddText(a);
		Debug->EndLine();
		
		if (a <= 40)
		{
			direction *= speed;
			D3DXVECTOR3 pos(enemyPos.x + direction.x, enemyPos.y, enemyPos.z + direction.z);
			sprEnemy->SetPosition(&pos);
			sprEnemy->Update();
		}
	}
	for (m_iterMonster = m_vecMonster.begin(); m_iterMonster != m_vecMonster.end(); m_iterMonster++)
	{
		(*m_iterMonster)->Update();
	}


}

void MonsterManager::Render()
{
	for (m_iterMonster = m_vecMonster.begin(); m_iterMonster != m_vecMonster.end(); m_iterMonster++)
	{
		(*m_iterMonster)->Render();
	}
}

void MonsterManager::MonsterSetup(char * fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Monster* m_pMonster = new Monster;
	m_pMonster->Init(fileName, pos, rot);
	m_vecMonster.push_back(m_pMonster);


}

