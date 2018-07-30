#pragma once
#include "IScene.h"

class IMap;
class ObjMap;
class Player;
class SkyBox;
class Picking;
class ItemManager;
class Collision;
class MonsterManager;
class EnemyManager;
class BulletManager;
class OBB;
class Minimap;

class SceneObjMap : public IScene
{
private:
	ObjMap *		m_pObjMap;
	Player *		m_pPlayer;
	SkyBox *		m_pSkyBox;
	Picking *		m_pPicking;
	ItemManager *   m_pItemManager;
	Minimap *		m_pMinimap;
	Collision*		m_pCollision;
	MonsterManager*	m_pMonsterManager;
	EnemyManager*	m_pEnemyManager;
	BulletManager*	m_pBulletManager;

public:
	SceneObjMap();
	~SceneObjMap();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

