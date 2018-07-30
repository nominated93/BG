#pragma once

#include "IDisplayObject.h"

class Player;
class BulletManager;
class ItemManager;
class Inventory;
class ItemBox;
class Collision :public IDisplayObject
{
private:
	Player * m_pPlayer;
	Inventory*		m_pInven;
	BulletManager*	m_pBM;
	ItemManager*	m_pIM;
	ItemBox*		m_pItemBox;

public:
	Collision();
	~Collision();

public:
	void Init();
	void Init(Player * pPlayer, BulletManager* pBM, ItemManager* pIM, Inventory* pInven, ItemBox* pItemBox);
	void Update();
	void Render();

public:
	bool CheckSphereIntersect(D3DXVECTOR3 vCenter1, float fRadius1, D3DXVECTOR3 vCenter2, float fRadius2);
	void Collision_ItemBoxPlayer();
	void Collision_ItemPlayer();
};

