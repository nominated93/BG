#pragma once

class Mesh
{
protected:
	LPD3DXMESH			m_pMesh;
	LPD3DXBUFFER		m_pSubsetBuff;
	DWORD				m_dwSubsetCount;

	LPD3DXMATERIAL		m_pSubsets;

	LPDIRECT3DTEXTURE9* m_pTextures;
	D3DMATERIAL9*		m_pMtrls;

public:
	Mesh();
	~Mesh();

	HRESULT CreateMesh(char* szPath, char* szFileName);
	void Render();
	void Release();
};

