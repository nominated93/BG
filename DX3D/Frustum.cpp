#include "stdafx.h"
#include "Frustum.h"


Frustum::Frustum()
{
}


Frustum::~Frustum()
{
}


void Frustum::Init()
{
	m_vVertex[0].x = -1.0f; m_vVertex[0].y = -1.0f; m_vVertex[0].z = 0.0f;
	m_vVertex[1].x = 1.0f; m_vVertex[1].y = -1.0f; m_vVertex[1].z = 0.0f;
	m_vVertex[2].x = 1.0f; m_vVertex[2].y = -1.0f; m_vVertex[2].z = 1.0f;
	m_vVertex[3].x = -1.0f; m_vVertex[3].y = -1.0f; m_vVertex[3].z = 1.0f;
	m_vVertex[4].x = -1.0f; m_vVertex[4].y = 1.0f; m_vVertex[4].z = 0.0f;
	m_vVertex[5].x = 1.0f; m_vVertex[5].y = 1.0f; m_vVertex[5].z = 0.0f;
	m_vVertex[6].x = 1.0f; m_vVertex[6].y = 1.0f; m_vVertex[6].z = 1.0f;
	m_vVertex[7].x = -1.0f; m_vVertex[7].y = 1.0f; m_vVertex[7].z = 1.0f;


	D3DXMATRIXA16 matView, matProj, matViewProj;
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	matViewProj = matView * matProj;

	D3DXMATRIXA16 matInv;
	D3DXMatrixInverse(&matInv, NULL, &matViewProj);

	for (int i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&m_vVertex[i], &m_vVertex[i], &matInv);

	}

	m_pos = (m_vVertex[0] + m_vVertex[5]) / 2.0f;

	D3DXPlaneFromPoints(&m_plane[0], &m_vVertex[4], &m_vVertex[7], &m_vVertex[6]); // 상 평면(top)
	D3DXPlaneFromPoints(&m_plane[1], &m_vVertex[0], &m_vVertex[1], &m_vVertex[2]); // 하 평면(bottom)
	D3DXPlaneFromPoints(&m_plane[2], &m_vVertex[0], &m_vVertex[4], &m_vVertex[5]); // 근 평면(near)
	D3DXPlaneFromPoints(&m_plane[3], &m_vVertex[2], &m_vVertex[6], &m_vVertex[7]); // 원 평면(far)
	D3DXPlaneFromPoints(&m_plane[4], &m_vVertex[0], &m_vVertex[3], &m_vVertex[7]); // 좌 평면(left)
	D3DXPlaneFromPoints(&m_plane[5], &m_vVertex[1], &m_vVertex[5], &m_vVertex[6]); // 우 평면(right)
}

BOOL Frustum::isIn(D3DXVECTOR3 * pv)
{
	float fDist;
	fDist = D3DXPlaneDotCoord(&m_plane[3], pv);
	if (fDist > 0) return FALSE;
	fDist = D3DXPlaneDotCoord(&m_plane[4], pv);
	if (fDist > 0) return FALSE;
	fDist = D3DXPlaneDotCoord(&m_plane[5], pv);
	if (fDist > 0) return FALSE;


	return TRUE;
}

BOOL Frustum::isInSphere(D3DXVECTOR3 * pv, float radius)
{
	float fDist;

	fDist = D3DXPlaneDotCoord(&m_plane[0], pv);
	if (fDist > (radius)) return FALSE;
	fDist = D3DXPlaneDotCoord(&m_plane[1], pv);
	if (fDist > (radius)) return FALSE;
	fDist = D3DXPlaneDotCoord(&m_plane[2], pv);
	if (fDist > (radius)) return FALSE;
	fDist = D3DXPlaneDotCoord(&m_plane[3], pv);
	if (fDist > (radius)) return FALSE;
	fDist = D3DXPlaneDotCoord(&m_plane[4], pv);
	if (fDist > (radius)) return FALSE;
	fDist = D3DXPlaneDotCoord(&m_plane[5], pv);
	if (fDist > (radius)) return FALSE;

	return TRUE;
}
