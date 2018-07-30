#include "stdafx.h"
#include "Monster.h"
#include "SkinnedMesh.h"
#include "OBB.h"


Monster::Monster()
	:m_pSkinnedMesh(NULL)
	, m_pOBB(NULL)
{
}


Monster::~Monster()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void Monster::Init()
{
}

void Monster::Init(char* fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pOBB = new OBB;
	m_pOBB->Init(D3DXVECTOR3(-30.0f, 0.0f, -30.0f), D3DXVECTOR3(30.0f, 160.0f, 30.0f));

	m_pSkinnedMesh = new SkinnedMesh();
	m_pSkinnedMesh->SetPosition(&D3DXVECTOR3(900, 0, 0));
	m_pos = pos;
	m_rot = rot;
	m_pSkinnedMesh->Setup("resources/player", fileName);
}

void Monster::Update()
{
	//SetAnimationIndexBlend(GetRandomFloat(1,20));
	//m_pSkinnedMesh->Update();
	m_pOBB->Update(&m_matWorld);
}

void Monster::Render()
{
	D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld;

	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationX(&matRX, D3DX_PI / 2);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y - 60, m_pos.z);

	matWorld = matS * matRX * matRY * matT;

	m_pSkinnedMesh->Render(NULL, &matWorld);
	m_pOBB->Render_Debug(255);
}

void Monster::SetAnimationIndexBlend(int nIndex)
{
	m_pSkinnedMesh->SetAnimationIndexBlend(nIndex);
}

