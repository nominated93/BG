#include "stdafx.h"
#include "Enemy.h"
#include "SkinnedMesh.h"
#include "Player.h"
#include "BulletManager.h"
#include "OBB.h"
#include "Mesh.h"
#include "IMap.h"


Enemy::Enemy()
	: m_pSkinnedMesh(NULL)
	, m_pPlayer(NULL)
	, m_pGun(NULL)
	, m_pBulletsManager(NULL)
	, m_pAniController(NULL)
	, m_pAniSet(NULL)
	, m_isBlend(false)
	, m_fBlendTime(0.5f)
	, m_fPassedBlendTime(0.0f)
	, m_pOBB(NULL)
	, m_pAniController2(NULL)
	, m_vDirForMoving(0, 0, 0)
	, m_pMap(NULL)
	, m_isMove(true)
{
	ZeroMemory(&m_stTrackDesc, sizeof(D3DXTRACK_DESC));

}
Enemy::~Enemy()
{
	SAFE_DELETE(particle);
	SAFE_RELEASE(m_pAniController);
	SAFE_RELEASE(m_pAniSet);
	SAFE_DELETE(m_pOBB);
	SAFE_RELEASE(m_pAniController2);
}

void Enemy::Init()
{
}

void Enemy::Init(Player* player, std::string keyName, BulletManager* bulletsManager, IMap* map)
{

	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Action");
	m_pSkinnedMesh->GetAnimationController()->CloneAnimationController(m_pSkinnedMesh->GetAnimationController()->GetMaxNumAnimationOutputs(),
		m_pSkinnedMesh->GetAnimationController()->GetMaxNumAnimationSets(),
		m_pSkinnedMesh->GetAnimationController()->GetMaxNumTracks(),
		m_pSkinnedMesh->GetAnimationController()->GetMaxNumEvents(),
		&m_pAniController2);
	//m_pAniController2 = m_pSkinnedMesh->GetAnimationController();

	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh(keyName);

	m_pPlayer = player;

	m_IsAlive = false;

	m_pBulletsManager = bulletsManager;

	m_pSkinnedMesh->GetAnimationController()->CloneAnimationController(m_pSkinnedMesh->GetAnimationController()->GetMaxNumAnimationOutputs(),
		m_pSkinnedMesh->GetAnimationController()->GetMaxNumAnimationSets(),
		m_pSkinnedMesh->GetAnimationController()->GetMaxNumTracks(),
		m_pSkinnedMesh->GetAnimationController()->GetMaxNumEvents(),
		&m_pAniController);
	//m_pAniController = m_pSkinnedMesh->GetAnimationController();

	m_pOBB = new OBB;
	m_pOBB->Init(D3DXVECTOR3(-30.0f, -60.0f, -30.0f), D3DXVECTOR3(30.0f, 160.0f, 30.0f));

	m_pGun = g_pMeshManager->GetStaticMesh("AK-47");
	D3DXVec3Normalize(&m_vDirForMoving, &m_vDirForMoving);

	m_pMap = map;

	particle = new EnemyParticle(100, 20);
	particle->Init("resources/particle/blood.png");


}
void Enemy::reMake(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int patternNum)
{
	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Character");
	m_nMaxHp = 100;
	m_nCurrentHp = 100;

	m_pos = pos;
	m_rot = dir;
	m_IsAlive = true;

	m_ePattern = Pattern_IDLE;

	m_nAniIndex = 1;

	SetAnimationIndex(38);
	m_nAmmoRemain = 5;
	m_fAttackPatternCount = 0.0f;
	m_fReloadPatternCount = 0.0f;
	m_fEndPatternCount = 0.0f;

	m_vMoveStartPos = m_pos;

	m_nPatternNum = patternNum;
	if (m_nPatternNum == 0)
	{
		SetAnimationIndexBlend(38);
		m_ePattern = Pattern_ATTACK;
	}
	if (m_nPatternNum == 1)
	{
		SetAnimationIndexBlend(32);
		m_ePattern = Pattern_MOVE_LEFT;
		m_vMoveStartPos = m_pos;
	}
	if (m_nPatternNum == 2)
	{
		SetAnimationIndexBlend(28);
		m_ePattern = m_ePattern = Pattern_MOVE_RIGHT;
		m_vMoveStartPos = m_pos;
	}

	m_vDirForMoving = dir;
	D3DXVec3Normalize(&m_vDirForMoving, &m_vDirForMoving);
}

void Enemy::Update()
{
	float length = GetLength();

	SetDirByGetPlayerPos();

	SetWorldMat();

	m_pOBB->Update(&m_matWorld);

	if( m_ePattern != Pattern_Dying &&
		m_ePattern != Pattern_End)
	{
		Move();
	}

	if (g_pKeyboardManager->isOnceKeyDown('O'))
	{
		BulletHit(30);
	}

	if (m_ePattern == Pattern_Move)
	{
		/*Move();*/
	}

	if (m_ePattern == Pattern_ATTACK)
	{
		if (length >= 50 && length <= 30)
		{
			AttackPattern();
		}
	}
	if (m_ePattern == Pattern_RELOAD)
	{
		ReloadPattern();
	}
	if (m_ePattern == Pattern_Dying)
	{
		LPD3DXKEYFRAMEDANIMATIONSET aniset = NULL;
		D3DXTRACK_DESC td;

		m_pAniController2->GetTrackAnimationSet(0, (LPD3DXANIMATIONSET*)&aniset);
		m_pAniController2->GetTrackDesc(0, &td);

		particle->Update(0.5f);

		if (td.Position > aniset->GetPeriod())
		{
			LPD3DXANIMATIONSET	pAnimSet = NULL;
			m_pAniController2->GetAnimationSet(0, &pAnimSet);
			m_pAniController2->SetTrackAnimationSet(0, pAnimSet);

			SAFE_RELEASE(pAnimSet);
			m_ePattern = Pattern_End;

			SAFE_RELEASE(aniset);

		}
	}
	if (m_ePattern == Pattern_End)
	{

		m_fEndPatternCount += g_pTimeManager->GetEllapsedTime();
		if (m_fEndPatternCount >= 60 * g_pTimeManager->GetEllapsedTime())
		{
			m_IsAlive = false;
			m_fEndPatternCount = 0.0f;
			m_pOBB->Init(D3DXVECTOR3(-30.0f, -60, -30.0f), D3DXVECTOR3(30.0f, 160.0f, 30.0f));
		}
	}
	if (m_ePattern == Pattern_MOVE_LEFT)
	{
		MoveLeftPattern();
	}
	if (m_ePattern == Pattern_MOVE_RIGHT)
	{
		MoveRightPattern();
	}

	float nTime = 0;
	if (m_isBlend)
	{
		m_pAniController->GetTrackDesc(0, &m_stTrackDesc);
		m_pAniController->GetTrackAnimationSet(0, &m_pAniSet);
		nTime = m_stTrackDesc.Position / m_pAniSet->GetPeriod();
		m_fPassedBlendTime += g_pTimeManager->GetEllapsedTime();
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_pAniController->SetTrackWeight(0, 1.0f);
			m_pAniController->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAniController->SetTrackWeight(0, fWeight);
			m_pAniController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}
}

void Enemy::Render()
{

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pSkinnedMesh)
	{
		if (m_pSkinnedMesh == g_pSkinnedMeshManager->GetSkinnedMesh("Character"))
		{
			m_pAniController->AdvanceTime(g_pTimeManager->GetEllapsedTime() * 1.2f, NULL);
		}
		else
		{
			m_pAniController2->AdvanceTime(g_pTimeManager->GetEllapsedTime() * 1.2f, NULL);
		}
		m_pSkinnedMesh->Update(m_pSkinnedMesh->GetRoot(), NULL);
		m_pSkinnedMesh->UpdateSkinnedMesh(m_pSkinnedMesh->GetRoot());
		m_pSkinnedMesh->Render(NULL, &m_matWorld);
	}

	D3DXMATRIXA16 matBone, matWorld;
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, D3DX_PI);

	if (m_pSkinnedMesh == g_pSkinnedMeshManager->GetSkinnedMesh("Character"))
	{
		g_pSkinnedMeshManager->GetBoneMatrix("Character", "hand_r", matBone);
	}
	else
	{
		g_pSkinnedMeshManager->GetBoneMatrix("Action", "hand_r", matBone);
	}

	matWorld = matBone * matR * m_matWorld;
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (m_pGun)
	{
		m_pGun->Render();
	}

	if(m_ePattern == Pattern_Dying)
	{
		particle->Render();
	}

	m_pOBB->Render_Debug(255);
}

void Enemy::SetAniByIndex()
{
	m_pSkinnedMesh->SetAnimationIndex(m_nAniIndex);
}

void Enemy::SkinnedMeshUpdate()
{
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();
}

void Enemy::SetAnimationIndex(int nIndex)
{
	LPD3DXANIMATIONSET	pAnimSet = NULL;
	m_pAniController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAniController->SetTrackAnimationSet(0, pAnimSet);

	SAFE_RELEASE(pAnimSet);
}

void Enemy::SetAnimationIndexBlend(int nIndex)
{
	m_isBlend = true;
	m_fPassedBlendTime = 0.0f;

	LPD3DXANIMATIONSET	pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET	pNextAnimSet = NULL;
	D3DXTRACK_DESC stTrackDesc;

	m_pAniController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAniController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAniController->SetTrackDesc(1, &stTrackDesc);

	m_pAniController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAniController->SetTrackAnimationSet(0, pNextAnimSet);

	m_pAniController->SetTrackWeight(0, 0.0f);
	m_pAniController->SetTrackWeight(1, 1.0f);

	m_pAniController->GetAnimationSet(nIndex, &m_pAniSet);
	m_pAniController->SetTrackAnimationSet(0, m_pAniSet);

	m_pAniController->SetTrackPosition(0, 0);
	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);
}

void Enemy::BulletHit(int damage)
{
	int prevHP;
	prevHP = m_nCurrentHp;
	m_nCurrentHp -= damage;
	if (m_nCurrentHp <= 0 && prevHP >0)
	{
		m_ePattern = Pattern_Dying;
		m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Action");
		LPD3DXANIMATIONSET	pAnimSet = NULL;
		m_pAniController2->GetAnimationSet(1, &pAnimSet);
		m_pAniController2->SetTrackAnimationSet(0, pAnimSet);

		SAFE_RELEASE(pAnimSet);
	}
}

void Enemy::SetWorldMat()
{
	D3DXMATRIXA16 matS, matR, matRY, matT;

	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	D3DXMatrixIdentity(&matRY);
	D3DXMatrixRotationY(&matRY, D3DX_PI);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	float fTemp;
	fTemp = acosf(m_rot.z);
	if (m_rot.x <= 0.0f)
	{
		fTemp = (2 * D3DX_PI) - fTemp;
	}
	fTemp += D3DX_PI;
	D3DXMatrixRotationY(&matR, fTemp);

	m_matWorld = matS * matR * matRY * matT;
}

void Enemy::SetDirByGetPlayerPos()
{
	m_rot = (m_pPlayer->GetPosition() - m_pos);
	D3DXVec3Normalize(&m_rot, &m_rot);
}

void Enemy::BulletFire()
{
	m_pBulletsManager->Fire(10, 1.0f, 100.0f, &(m_pos + D3DXVECTOR3(0.0f, 1.0f, 0.0f) + 1.2f * m_rot), &m_rot);
}

void Enemy::AttackPattern()
{
	if (m_nAmmoRemain <= 0)
	{
		if (m_nPatternNum == 0)
		{
			SetAnimationIndexBlend(18);
			m_ePattern = Pattern_RELOAD;
			m_pOBB->Init(D3DXVECTOR3(-30.0f, -60, -30.0f), D3DXVECTOR3(30.0f, 100.0f, 30.0f));
			return;
		}
		if (m_nPatternNum == 1)
		{
			SetAnimationIndexBlend(28);
			m_ePattern = Pattern_MOVE_RIGHT;
			m_vMoveStartPos = m_pos;
			return;
		}
		if (m_nPatternNum == 2)
		{
			SetAnimationIndexBlend(32);
			m_ePattern = Pattern_MOVE_LEFT;
			m_vMoveStartPos = m_pos;
			return;
		}

	}
	m_fAttackPatternCount++;
	if (m_fAttackPatternCount >= 50)
	{
		BulletFire();
		m_nAmmoRemain -= 1;
		m_fAttackPatternCount = 0.0f;
	}

}

void Enemy::ReloadPattern()
{
	m_fReloadPatternCount += g_pTimeManager->GetEllapsedTime();
	if (m_fReloadPatternCount >= 200 * g_pTimeManager->GetEllapsedTime())
	{
		m_fReloadPatternCount = 0.0f;
		m_nAmmoRemain = 5;
		m_pOBB->Init(D3DXVECTOR3(-30.0f, -60, -30.0f), D3DXVECTOR3(30.0f, 160.0f, 30.0f));
		if (m_nPatternNum == 0)
		{
			SetAnimationIndexBlend(38);
			m_ePattern = Pattern_ATTACK;
			return;
		}
		if (m_nPatternNum == 1)
		{
			SetAnimationIndexBlend(32);
			m_ePattern = Pattern_MOVE_LEFT;
			m_vMoveStartPos = m_pos;
			return;
		}
		if (m_nPatternNum == 2)
		{
			SetAnimationIndexBlend(28);
			m_ePattern = m_ePattern = Pattern_MOVE_RIGHT;
			m_vMoveStartPos = m_pos;
			return;
		}
	}
}

void Enemy::MoveLeftPattern()
{
	//이동이랑 관련된 코드
	float speed;
	speed = 0.5f;
	D3DXVECTOR3 moveDirTemp;
	D3DXVec3Cross(&moveDirTemp, &D3DXVECTOR3(m_vDirForMoving.x, -60, m_vDirForMoving.z), &D3DXVECTOR3(0, 1.0f, 0));
	D3DXVec3Normalize(&moveDirTemp, &moveDirTemp);
	m_pos.x += speed * moveDirTemp.x;
	m_pos.z += speed * moveDirTemp.z;

	//이동이 끝났다면
	if (D3DXVec3Length(&(m_pos - m_vMoveStartPos)) >= 2.0f)
	{
		if (m_nPatternNum == 2)
		{
			SetAnimationIndexBlend(18);
			m_ePattern = Pattern_RELOAD;
			m_pOBB->Init(D3DXVECTOR3(-30.0f, -60, -30.0f), D3DXVECTOR3(30.0f, 100.0f, 30.0f));
			return;
		}
		if (m_nPatternNum == 1)
		{
			SetAnimationIndexBlend(38);
			m_ePattern = Pattern_ATTACK;
		}
	}
}

void Enemy::MoveRightPattern()
{
	//이동이랑 관련된 코드
	float speed;
	speed = 0.5f;
	D3DXVECTOR3 moveDirTemp;
	D3DXVec3Cross(&moveDirTemp, &D3DXVECTOR3(m_vDirForMoving.x, 0, m_vDirForMoving.z), &D3DXVECTOR3(0, 1.0f, 0));
	D3DXVec3Normalize(&moveDirTemp, &moveDirTemp);
	m_pos.x -= speed * moveDirTemp.x;
	m_pos.z -= speed * moveDirTemp.z;

	//이동이 끝났다면
	if (D3DXVec3Length(&(m_pos - m_vMoveStartPos)) >= 2.0f)
	{
		if (m_nPatternNum == 1)
		{
			SetAnimationIndexBlend(18);
			m_ePattern = Pattern_RELOAD;
			m_pOBB->Init(D3DXVECTOR3(-30.0f, -60.0f, -30.0f), D3DXVECTOR3(30.0f, 100.0f, 30.0f));
			return;
		}
		if (m_nPatternNum == 2)
		{
			SetAnimationIndexBlend(38);
			m_ePattern = Pattern_ATTACK;
		}
	}
}

float Enemy::GetLength()
{
	float a;
	D3DXVECTOR3 playerPos = m_pPlayer->GetPosition();
	D3DXVECTOR3 enemyPos = GetPosition();
	D3DXVECTOR3 direction = playerPos - enemyPos;
	D3DXVECTOR3 length = playerPos - enemyPos;

	// 방향벡터 정규화
	D3DXVec3Normalize(&direction, &direction);
	a = D3DXVec3Length(&length);
	
	return a;
}


void Enemy::Move()
{

	float a;
	D3DXVECTOR3 playerPos = m_pPlayer->GetPosition();

	// 추격 스피드
	float speed = 0.5;
	// 적 위치 구하기
	D3DXVECTOR3 enemyPos = GetPosition();
	// 플레이어 위치에서 적 위치를 빼서
	// 플레이어로 향하는 벡터 구하기
	D3DXVECTOR3 direction = playerPos - enemyPos;
	D3DXVECTOR3 length = playerPos - enemyPos;
	//length.y = 0;

	// 방향벡터 정규화
	D3DXVec3Normalize(&direction, &direction);
	a = GetLength();

	if (a <= 50 && a >= 30) {
		direction *= speed;
		D3DXVECTOR3 pos(enemyPos.x + direction.x, enemyPos.y, enemyPos.z + direction.z);
		SetPosition(&pos);

		m_fReloadPatternCount += g_pTimeManager->GetEllapsedTime();
		if (m_fReloadPatternCount >= 200 * g_pTimeManager->GetEllapsedTime())
		{
			m_fReloadPatternCount = 0.0f;
			m_nAmmoRemain = 5;
			//m_pOBB->Init(D3DXVECTOR3(-30.0f, -60, -30.0f), D3DXVECTOR3(30.0f, 160.0f, 30.0f));

			SetAnimationIndexBlend(19);
			m_ePattern = Pattern_Move;
			m_vMoveStartPos = enemyPos;

		}
	}
}