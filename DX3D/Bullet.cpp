#include "stdafx.h"
#include "Bullet.h"


void Bullet::Init(float damage, float speed, float range, D3DXVECTOR3* pos, D3DXVECTOR3* dir)
{
	m_fDamage = damage;
	m_fSpeed = speed;
	m_fRange = range;
	m_pos = *pos;
	m_rot = *dir;
	m_isAlive = true;
	firstPos = *pos;

	float radius = 0.2f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);

}

void Bullet::Update()
{
	D3DXVECTOR3 temp;
	temp = m_pos - firstPos;
	float tempDist;

	tempDist = D3DXVec3Length(&temp);
	if (tempDist >= m_fRange)
	{
		m_isAlive = false;
	}
}

void Bullet::Render()
{
	D3DXMATRIXA16 matS, matR, matT, matWorld;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	
	m_pos = m_pos + (m_rot * 5.0f);

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	matWorld = matS * matR * matT;

	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pDevice->SetTexture(0, NULL);
	m_pSphere->DrawSubset(0);
}

Bullet::Bullet()
{
	m_isAlive = false;
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

