#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	Release();
}


HRESULT Mesh::CreateMesh(char* szPath, char* szFileName)
{

	std::string sFullPath(szPath);
	sFullPath += (std::string("/") + std::string(szFileName));

	if (FAILED(D3DXLoadMeshFromX(sFullPath.c_str(), D3DXMESH_MANAGED, g_pDevice, NULL, &m_pSubsetBuff, NULL, &m_dwSubsetCount, &m_pMesh)))
		return E_FAIL;

	m_pSubsets = (D3DXMATERIAL*)m_pSubsetBuff->GetBufferPointer();
	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwSubsetCount];
	m_pMtrls = new D3DMATERIAL9[m_dwSubsetCount];


	for (DWORD i = 0; i < m_dwSubsetCount; i++)
	{
		m_pMtrls[i] = m_pSubsets[i].MatD3D;
		m_pMtrls[i].Emissive = m_pMtrls[i].Ambient = m_pMtrls[i].Diffuse;

		std::string szFullPath(szPath);
		szFullPath += (std::string("/") + m_pSubsets[i].pTextureFilename);

		if (FAILED(D3DXCreateTextureFromFile(g_pDevice, szFullPath.c_str(), &m_pTextures[i])))
			return E_FAIL;
	}

	return S_OK;
}

void Mesh::Render()
{
	for (DWORD i = 0; i < m_dwSubsetCount; i++)
	{
		g_pDevice->SetMaterial(&m_pMtrls[i]);
		g_pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}

void Mesh::Release()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pSubsetBuff);

	if (m_pTextures)
	{
		for (DWORD i = 0; i < m_dwSubsetCount; i++)
			SAFE_RELEASE(m_pTextures[i]);

		delete[] m_pTextures;
		m_pTextures = NULL;
	}
	if (m_pMtrls)
	{
		delete[] m_pMtrls;
		m_pMtrls = NULL;
	}
}
