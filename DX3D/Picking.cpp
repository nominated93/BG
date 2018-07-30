#include "stdafx.h"
#include "Picking.h"
#include "Ray.h"

Picking::Picking()
{
	m_pSphere = NULL;
}


Picking::~Picking()
{
	SAFE_RELEASE(m_pSphere);
	for (auto p : m_vecBoundary)
		SAFE_DELETE(p);
}

void Picking::Init()
{
	int dim = 1;
	float radius = 1.2f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);

	
	m_vecBoundary.reserve(dim * dim * dim);
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				BoundingSphere* s = new BoundingSphere(D3DXVECTOR3(5, -60, -70), radius);
				m_vecBoundary.push_back(s);
			}
		}
	}
}


void Picking::Update()
{

}

void Picking::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	for (auto p : m_vecBoundary)
	{
		if (p->isPicked == true)
		{
			g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
			
		}
		else
		{
			g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
		}
		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, p->center.x, p->center.y, p->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphere->DrawSubset(0);
	}
}

void Picking::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->SetIsFire(true);
		//Ray r = Ray::RayAtWorldSpace(SCREEN_POINT(lParam));

		float vpWidth = rc.right - rc.left;
		float vpHeight = rc.bottom - rc.top;

		Ray r = Ray::RayAtWorldSpace(vpWidth / 2, vpHeight / 2);
		for (auto p : m_vecBoundary)
		{
			//p->isPicked = r.CalcIntersectSphere(p);
		}
		BoundingSphere* sphere = NULL;
		float minDistance = FLT_MAX;
		float intersectionDistance;
		for (auto p : m_vecBoundary)
		{
			p->isPicked = false;
			if (r.CalcIntersectSphere(p) == true)
			{
				intersectionDistance = D3DXVec3Length(&(p->center - r.m_pos));
				if (intersectionDistance < minDistance)
				{
					minDistance = intersectionDistance;
					sphere = p;
				}
			}
		}
		if (sphere != NULL)
		{
			sphere->isPicked = true;
		}
	}
	break;
	default:
		static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->SetIsFire(false);
		break;
	}
}
