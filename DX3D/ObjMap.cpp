#include "stdafx.h"
#include "ObjMap.h"
#include "DrawingGroup.h"
#include "ObjLoader.h"

ObjMap::ObjMap()
{
	m_rayOffsetY = 5;
}


ObjMap::~ObjMap()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RELEASE(p);
	SAFE_RELEASE(m_pMesh);
	for (auto p : m_vecMtlTex)
		SAFE_DELETE(p);
}

void ObjMap::Init()
{
	D3DXMATRIXA16 matView, matInvView;
	g_pDevice->GetTransform(D3DTS_WORLD, &matView);
	D3DXMatrixInverse(&matInvView, NULL, &matView);
	D3DXVec3TransformCoord(&m_pos, &m_pos, &matView);

	//D3DXMATRIXA16 matRX, matRY, matS, matWorld;
	D3DXMATRIXA16 matS, matT, matRY, matWorld;
	//D3DXMatrixRotationX(&matRX, -D3DX_PI / 2.0f);
	D3DXMatrixIdentity(&matRY);
	//D3DXMatrixRotationY(&matRY, D3DX_PI);


	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 0.15f, 0.15f, 0.15f);
	//D3DXMatrixTranslation(&matT, 0, 0, 0);
	//matWorld = matS * matRX * matRY;
	//m_matWorld = matS * matRY * matT;
	matWorld = matS;

	ObjLoader loader;
	//loader.Load("resources/obj/cs_militia/", "cs_militia.obj", &matWorld, m_vecDrawingGroup);
	//loader.Load("resources/obj", "map_surface.obj", &matWorld, m_vecDrawingGroup);

	m_pMesh = loader.LoadMesh("resources/obj/cs_office/", "cs_office.obj", &matWorld, m_vecMtlTex);
	loader.CreateSurface(m_vecVertex);

	//loader.LoadSurface("resources/obj/map_surface.obj", &matWorld, m_vecVertex);
	g_pMapManager->AddMap("ObjMap", this);
	g_pMapManager->SetCurrentMap("ObjMap");
}

void ObjMap::Update()
{
}


void ObjMap::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//RenderDrawingGroup();
	RenderMesh();
	//RenderDrawSpeed();
	//RenderEachSubset();
	//RenderSurface();
}

bool ObjMap::GetHeight(OUT float & height, const D3DXVECTOR3 & pos)
{
	/*
	D3DXVECTOR3 rayPos(pos.x, pos.y + m_rayOffsetY, pos.z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float distance;
	float tmpHeight;
	float highest = -99999;
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1], &m_vecVertex[i + 2],
			&rayPos, &rayDir, NULL, NULL, &distance))
		{
			tmpHeight = rayPos.y - distance;

			if (tmpHeight > highest + FLT_EPSILON)
			{
				highest = tmpHeight;
				height = tmpHeight;
			}
		}
	}

	if (highest == -99999)
		return false;
	else
		return true;
		*/
	D3DXVECTOR3 rayPos(pos.x, pos.y + m_rayOffsetY, pos.z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float distance;

	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1],
			&m_vecVertex[i + 2], &rayPos, &rayDir, 0, 0, &distance))
		{
			height = rayPos.y - distance;
			return true;
		}
	}
	return false;
}

void ObjMap::RenderDrawingGroup()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RENDER(p);
}

void ObjMap::RenderMesh()
{
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
		g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
		m_pMesh->DrawSubset(i);
	}
}


void ObjMap::RenderEachSubset()
{
	static int nSubSet = 0;

	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		--nSubSet;
		if (nSubSet < 0) nSubSet = 0;
	}
	else if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		++nSubSet;
		if (nSubSet > m_vecMtlTex.size() - 1) nSubSet = m_vecMtlTex.size() - 1;
	}

	g_pDevice->SetMaterial(&m_vecMtlTex[nSubSet]->GetMaterial());
	g_pDevice->SetTexture(0, m_vecMtlTex[nSubSet]->GetTexture());
	m_pMesh->DrawSubset(nSubSet);
}

void ObjMap::RenderDrawSpeed()
{
	DWORD start, finish;
	size_t drawCount = 100;
	start = GetTickCount();
	for (size_t cnt = 0; cnt < drawCount; cnt++)
	{
		RenderDrawingGroup();
	}
	finish = GetTickCount();

	static float sumTimeDrawingGroup = 0;
	sumTimeDrawingGroup += (finish - start) / 1000.0f;

	start = GetTickCount();
	for (size_t cnt = 0; cnt < drawCount; cnt++)
	{
		RenderMesh();
	}
	finish = GetTickCount();

	static float sumTimeMesh = 0;
	sumTimeMesh += (finish - start) / 1000.0f;

	Debug->AddText(sumTimeDrawingGroup);
	Debug->AddText(" / ");
	Debug->AddText(sumTimeMesh);
	Debug->AddText(" = ");
	Debug->AddText(sumTimeDrawingGroup / sumTimeMesh);
	Debug->EndLine();
}

void ObjMap::RenderSurface()
{
	g_pDevice->SetFVF(D3DFVF_XYZ);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(D3DXVECTOR3));
}