#include "stdafx.h"
#include "OBB.h"

OBB::OBB()
{
}


OBB::~OBB()
{
}

void OBB::Init(D3DXVECTOR3 _vMin, D3DXVECTOR3 _vMax)
{
	D3DXVECTOR3 vMin = _vMin;
	D3DXVECTOR3 vMax = _vMax;

	m_vOrgCenterPos = (vMin + vMax) / 2.0f;

	m_vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	D3DXMatrixIdentity(&m_matWorldTM);

}

void OBB::Update(D3DXMATRIXA16* pMatWorld)
{
	if (pMatWorld)
	{
		m_matWorldTM = (*pMatWorld);
	}

	for (int i = 0; i < 3; i++)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i],
			&m_vOrgAxisDir[i],
			&m_matWorldTM);
	}

	D3DXVec3TransformCoord(&m_vCenterPos,
		&m_vOrgCenterPos,
		&m_matWorldTM);
}

bool OBB::IsCollision(OBB * pObb1, OBB * pObb2)
{
	D3DXVECTOR3 vDist = pObb1->m_vCenterPos - pObb2->m_vCenterPos;
	D3DXVECTOR3 vSA;
	D3DXVECTOR3 vElement1[3];
	D3DXVECTOR3 vElement2[3];
	float r0, r1, r2;


	for (int i = 0; i < 3; i++)
	{
		vElement1[i] = pObb1->m_fAxisHalfLen[i] * pObb1->m_vAxisDir[i];
		vElement2[i] = pObb2->m_fAxisHalfLen[i] * pObb2->m_vAxisDir[i];
	}

	for (int i = 0; i<3; i++)
	{
		vSA = pObb1->m_vAxisDir[i];


		r1 = 0.f;
		r2 = 0.f;

		for (int n = 0; n < 3; n++)
		{
			r1 += fabs(D3DXVec3Dot(&vSA, &vElement1[n]));
			r2 += fabs(D3DXVec3Dot(&vSA, &vElement2[n]));
		}

		r0 = fabs(D3DXVec3Dot(&vSA, &(vDist)));
		if (r0 > r1 + r2) return false;
	}

	for (int i = 0; i<3; i++)
	{
		vSA = pObb2->m_vAxisDir[i];

		r1 = 0.f;
		r2 = 0.f;

		for (int n = 0; n < 3; n++)
		{
			r1 += fabs(D3DXVec3Dot(&vSA, &vElement1[n]));
			r2 += fabs(D3DXVec3Dot(&vSA, &vElement2[n]));
		}

		r0 = fabs(D3DXVec3Dot(&vSA, &(vDist)));
		if (r0 > r1 + r2) return false;
	}

	for (int _1 = 0; _1 < 3; _1++)
	{
		for (int _2 = 0; _2 < 3; _2++)
		{

			D3DXVec3Cross(&vSA, &pObb1->m_vAxisDir[_1], &pObb2->m_vAxisDir[_2]);

			r1 = 0.f;
			r2 = 0.f;

			for (int n = 0; n < 3; n++)
			{
				r1 += fabs(D3DXVec3Dot(&vSA, &vElement1[n]));
				r2 += fabs(D3DXVec3Dot(&vSA, &vElement2[n]));
			}

			r0 = fabs(D3DXVec3Dot(&vSA, &(vDist)));
			if (r0 > r1 + r2) return false;
		}
	}

	return true;
}


void OBB::Render_Debug(D3DCOLOR c)
{


	std::vector<VERTEX_PC> vecVertex;

	VERTEX_PC v[8];
	for (int i = 0; i < 8; i++)
	{
		v[i].c = c;
	}

	v[0].p = m_vCenterPos - m_fAxisHalfLen[0] * m_vAxisDir[0]
		+ m_fAxisHalfLen[1] * m_vAxisDir[1]
		+ m_fAxisHalfLen[2] * m_vAxisDir[2];
	
	v[1].p = m_vCenterPos - m_fAxisHalfLen[0] * m_vAxisDir[0]
		+ m_fAxisHalfLen[1] * m_vAxisDir[1]
		- m_fAxisHalfLen[2] * m_vAxisDir[2];

	v[2].p = m_vCenterPos + m_fAxisHalfLen[0] * m_vAxisDir[0]
		+ m_fAxisHalfLen[1] * m_vAxisDir[1]
		- m_fAxisHalfLen[2] * m_vAxisDir[2];

	v[3].p = m_vCenterPos + m_fAxisHalfLen[0] * m_vAxisDir[0]
		+ m_fAxisHalfLen[1] * m_vAxisDir[1]
		+ m_fAxisHalfLen[2] * m_vAxisDir[2];

	v[4].p = m_vCenterPos - m_fAxisHalfLen[0] * m_vAxisDir[0]
		- m_fAxisHalfLen[1] * m_vAxisDir[1]
		+ m_fAxisHalfLen[2] * m_vAxisDir[2];

	v[5].p = m_vCenterPos - m_fAxisHalfLen[0] * m_vAxisDir[0]
		- m_fAxisHalfLen[1] * m_vAxisDir[1]
		- m_fAxisHalfLen[2] * m_vAxisDir[2];

	v[6].p = m_vCenterPos + m_fAxisHalfLen[0] * m_vAxisDir[0]
		- m_fAxisHalfLen[1] * m_vAxisDir[1]
		- m_fAxisHalfLen[2] * m_vAxisDir[2];

	v[7].p = m_vCenterPos + m_fAxisHalfLen[0] * m_vAxisDir[0]
		- m_fAxisHalfLen[1] * m_vAxisDir[1]
		+ m_fAxisHalfLen[2] * m_vAxisDir[2];

	vecVertex.push_back(v[0]);
	vecVertex.push_back(v[1]);
	vecVertex.push_back(v[1]);
	vecVertex.push_back(v[2]);
	vecVertex.push_back(v[2]);
	vecVertex.push_back(v[3]);
	vecVertex.push_back(v[3]);
	vecVertex.push_back(v[0]);

	vecVertex.push_back(v[0]);
	vecVertex.push_back(v[4]);
	vecVertex.push_back(v[1]);
	vecVertex.push_back(v[5]);

	vecVertex.push_back(v[3]);
	vecVertex.push_back(v[7]);
	vecVertex.push_back(v[2]);
	vecVertex.push_back(v[6]);

	vecVertex.push_back(v[4]);
	vecVertex.push_back(v[5]);
	vecVertex.push_back(v[5]);
	vecVertex.push_back(v[6]);
	vecVertex.push_back(v[6]);
	vecVertex.push_back(v[7]);
	vecVertex.push_back(v[7]);
	vecVertex.push_back(v[4]);

	D3DXMATRIXA16 m_matWorldTM;
	D3DXMatrixIdentity(&m_matWorldTM);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetFVF(VERTEX_PC::FVF);

	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		vecVertex.size() / 2,
		&vecVertex[0],
		sizeof(VERTEX_PC));
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

}
