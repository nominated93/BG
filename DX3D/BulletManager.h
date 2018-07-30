#pragma once
#include "IDisplayObject.h"
#include "Bullet.h"

#define BULLETMAX 1000

class EnemyManager;
class Player;
class IMap;
class OBB;

class BulletManager : public IDisplayObject
{
private:

	vector<Bullet*>				m_vecBullet;
	vector<Bullet*>::iterator	m_iterBullet;

	Bullet						m_arrBullets[BULLETMAX];
	Player *					m_pPlayer;
	EnemyManager *				m_pEnemyManager;
	IMap *						m_pObjMap;
	D3DXVECTOR3 				tempPos;

public:
	BulletManager();
	~BulletManager();

	void Init();
	void Update();
	void Render();
	void Fire(float damage, float speed, float range, D3DXVECTOR3* pos, D3DXVECTOR3* dir);
	void Setup(Player* player, EnemyManager* enemyManager, IMap* map);
	void Remove();

};

