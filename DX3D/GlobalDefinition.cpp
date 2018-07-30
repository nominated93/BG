#include "stdafx.h"
#include "GlobalDefinition.h"

vector<D3DXVECTOR3> g_vecCubeVertex = {
	D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f, -1.0f,  1.0f),
	D3DXVECTOR3(-1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f, -1.0f,  1.0f)
};

vector<WORD> g_vecCubeIndex = {
	0, 1, 2, 0, 2, 3,	// ±Ù
	7, 6, 5, 7, 5, 4,	// ¿ø
	4, 5, 1, 4, 1, 0,	// ÁÂ
	3, 2, 6, 3, 6, 7,	// ¿ì
	1, 5, 6, 1, 6, 2,	// »ó
	4, 0, 3, 4, 3, 7	// ÇÏ
};

vector<vector<float>> g_vecCubeUV =
{
	{ 0, 1, 0, 0, 1, 0, 1, 1 },
	{ 0, 1, 0, 0, 1, 0, 1, 1 },
	{ 0, 1, 0, 0, 1, 0, 1, 1 },
	{ 0, 1, 0, 0, 1, 0, 1, 1 },
	{ 0, 1, 0, 0, 1, 0, 1, 1 },
	{ 0, 1, 0, 0, 1, 0, 1, 1 }
};

vector<D3DXVECTOR3> g_vecQuadVertex = {
	D3DXVECTOR3(-1, -1, 0),
	D3DXVECTOR3(-1, 1, 0),
	D3DXVECTOR3(1, 1, 0),
	D3DXVECTOR3(1, -1, 0)
};

vector<WORD> g_vecQuadIndex = {
	0, 1, 2, 0, 2, 3
};

vector<D3DXVECTOR2> g_vecQuadUV = {
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(1, 1)
};

DWORD FtoDw(float f) { return *((DWORD*)&f); }

float GetRandomFloat(float lowBound, float highBound)
{
	if (lowBound >= highBound) // bad input
		return lowBound;

	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f;

	// return float in [lowBound, highBound] interval. 
	return (f * (highBound - lowBound)) + lowBound;
}

bool CompareStr(const char * str1, const char * str2)
{
	return strcmp(str1, str2) == 0;
}

map<FontType, LPD3DXFONT> m_pFontList;
LPD3DXFONT GetFont(FontType type)
{
	//if (m_pFontList.find(type) == m_pFontList.end())
	//{
	if (type == FontType_NORMAL)
	{
		/*		if (FAILED(D3DXCreateFont(g_pDevice, 24, 12, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("µ¸¿òÃ¼"), &m_pFontList[type])))
		assert(false && "FAILED(D3DXCreateFont)");*/
		D3DXCreateFont(g_pDevice, 28, NULL, FW_NORMAL, 1, false, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Arial Black", &m_pFontList[type]);
	}
	else if (type == FontType_BULLETTOTAL)
	{
		//AddFontResource(_T("Fonts/umberto.ttf"));
		//if (FAILED(D3DXCreateFont(g_pDevice, 24, 12, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		//	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("umberto"), &m_pFontList[type])))
		//	assert(false && "FAILED(D3DXCreateFont)");

		D3DXCreateFont(g_pDevice, 14, NULL, FW_NORMAL, 1, false, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Arial Black", &m_pFontList[type]);
	}

	return m_pFontList[type];
}

namespace DXUtil
{

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Specular = s;
		mtrl.Emissive = e;
		mtrl.Power = p;

		return mtrl;
	}

	void ComputeNormal(D3DXVECTOR3* out, D3DXVECTOR3* p0, D3DXVECTOR3* p1, D3DXVECTOR3* p2)
	{
		D3DXVECTOR3 v01 = *p1 - *p0;
		D3DXVECTOR3 v02 = *p2 - *p0;

		D3DXVec3Cross(out, &v01, &v02);
		D3DXVec3Normalize(out, out);
	}

	D3DLIGHT9 InitDirectional(D3DXVECTOR3* dir, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Direction = *dir;

		return light;
	}

	D3DLIGHT9 InitPoint(D3DXVECTOR3* pos, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_POINT;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Position = *pos;
		light.Range = 20.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 0.005f;
		light.Attenuation1 = 0.005f;
		light.Attenuation2 = 0.005f;

		return light;
	}

	D3DLIGHT9 InitSpot(D3DXVECTOR3* dir, D3DXVECTOR3* pos, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_SPOT;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Direction = *dir;
		light.Position = *pos;
		light.Range = 50.0f;
		light.Falloff = 1.0f;
		light.Theta = 0.0f;
		light.Phi = D3DX_PI / 6;
		light.Attenuation0 = 0.005f;
		light.Attenuation1 = 0.005f;
		light.Attenuation2 = 0.005f;

		return light;
	}

	void InitVertexBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb, LPVOID vertices, DWORD fvf, UINT vtxCnt, UINT stride)
	{
		DX::GetDevice()->CreateVertexBuffer(vtxCnt * stride,
			NULL, fvf, D3DPOOL_MANAGED, &pVb, NULL);

		VERTEX_PNT* pVertex;
		pVb->Lock(0, 0, (LPVOID*)&pVertex, 0);
		memcpy(pVertex, vertices, vtxCnt * stride);
		pVb->Unlock();
	}

	void InitIndexBuffer(LPDIRECT3DINDEXBUFFER9 &pIb, LPVOID indices, UINT idxCnt, UINT stride)
	{
		D3DFORMAT format;
		if (stride == sizeof(WORD)) format = D3DFMT_INDEX16;
		else if (stride == sizeof(DWORD)) format = D3DFMT_INDEX32;

		DX::GetDevice()->CreateIndexBuffer(idxCnt * stride,
			NULL, format, D3DPOOL_MANAGED, &pIb, NULL);

		LPVOID pIndex;
		pIb->Lock(0, 0, (LPVOID*)&pIndex, 0);
		memcpy(pIndex, indices, idxCnt * stride);
		pIb->Unlock();
	}

}