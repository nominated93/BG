#include "stdafx.h"
#include "SceneObjMap.h"
#include "ObjMap.h"
#include "Player.h"
#include "SkyBox.h"
#include "Picking.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Collision.h"
#include "BulletManager.h"
#include "MonsterManager.h"
#include "EnemyManager.h"
#include "OBB.h"
#include "Minimap.h"

SceneObjMap::SceneObjMap()
{
	m_pSkyBox = NULL;
	m_pObjMap = NULL;
	m_pMinimap = NULL;
	m_pPlayer = NULL;
	m_pPicking = NULL;
	m_pCollision = NULL;
	m_pMonsterManager = NULL;
	m_pEnemyManager = NULL;
}


SceneObjMap::~SceneObjMap()
{
	OnDestructIScene();
}

void SceneObjMap::Init()
{
	g_pCamera->m_isLobby = false;

	//g_pCamera->Init();

	m_pSkyBox = new SkyBox("resources/skybox/sahara_up.tga",
		"resources/skybox/sahara_dn.tga",
		"resources/skybox/sahara_lf.tga",
		"resources/skybox/sahara_rt.tga",
		"resources/skybox/sahara_ft.tga",
		"resources/skybox/sahara_bk.tga");



	//g_pSkinnedMeshManager->Load("PlayerAction", "../../", "action.X");
	//g_pSkinnedMeshManager->Load("Action", "../../", "action.X");
	//g_pSkinnedMeshManager->Load("Character", "../../", "Character.X");

	//g_pMeshManager->AddMesh("AK-47", "resources/weapons", "AK-47.X"); //AK-47 추가
	//g_pMeshManager->AddMesh("Head", "resources/weapons", "F_Head_G_01.X");
	//g_pMeshManager->AddMesh("Armor", "resources/weapons", "F_Armor_C_01.X");
	//g_pMeshManager->AddMesh("Backpack", "resources/weapons", "F_Back_C_01_.X");

	m_pObjMap = new ObjMap; m_pObjMap->Init(); AddSimpleDisplayObj(m_pObjMap);
	m_pItemManager = new ItemManager; m_pItemManager->Init(); AddSimpleDisplayObj(m_pItemManager);

	m_pPlayer = new Player; m_pPlayer->AddressLink(m_pItemManager); m_pPlayer->Init();  AddSimpleDisplayObj(m_pPlayer);
	m_pEnemyManager = new EnemyManager; m_pEnemyManager->Init(); AddSimpleDisplayObj(m_pEnemyManager);
	m_pBulletManager = new BulletManager; m_pBulletManager->Setup(m_pPlayer, m_pEnemyManager, m_pObjMap); AddSimpleDisplayObj(m_pBulletManager);
	//m_pMonsterManager = new MonsterManager; m_pMonsterManager->Init(); AddSimpleDisplayObj(m_pMonsterManager);
	m_pPicking = new Picking; m_pPicking->Init(); AddSimpleDisplayObj(m_pPicking);
	m_pMinimap = new Minimap; m_pMinimap->Init(); AddSimpleDisplayObj(m_pMinimap);
	
	//Collision Init이 제일 뒤에 있어야됨
	m_pCollision = new Collision; m_pCollision->Init(m_pPlayer,		//플레이어
								m_pPlayer->GetPBulletManager(),		//볼렛메니저
												m_pItemManager,		//아이템매니저
										m_pPlayer->GetPInven(),		//인벤
						m_pPlayer->GetPInven()->GetPItemBox());		//아이템박스
	AddSimpleDisplayObj(m_pCollision);

	//test
	m_pPlayer->Init(m_pBulletManager);

	m_pEnemyManager->Init(m_pPlayer, m_pBulletManager, m_pObjMap);
	m_pEnemyManager->MakeEnemy(D3DXVECTOR3(16, -60, 0), D3DXVECTOR3(0, 0, 1), 0);
	m_pEnemyManager->MakeEnemy(D3DXVECTOR3(4, -60, 0), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->MakeEnemy(D3DXVECTOR3(12, -60, -99), D3DXVECTOR3(-0.07, 0, 0.99), 2);



	/*m_pEnemyManager->makeEnemy(D3DXVECTOR3(-69, -60, -101), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(-70, -60, -87), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(-112, -60, -115), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(-117, -60, -126), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(23, -60, -97), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(6, -60, -97), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(95, -60, -57), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(135, -60, -103), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(154, -60, -100), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(216, -60, 0), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(272, -60, -12), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(269, -60, -37), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(346, -60, -63), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(268, -60, -93), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(180, -60, -155), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(225, -60, -131), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(256, -60, -194), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(175, -60, -230), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(175, -60, -218), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(91, -60, -161), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(109, -60, -159), D3DXVECTOR3(0.8, 0, 0.6), 1);*/



	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void SceneObjMap::Update()
{
	//g_pCamera->Update();
	OnUpdateIScene();
}

void SceneObjMap::Render()
{
	m_pSkyBox->Render();
	OnRenderIScene();
}

void SceneObjMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pPicking);
}
