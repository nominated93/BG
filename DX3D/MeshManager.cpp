#include "stdafx.h"
#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
	Destroy();
}

HRESULT MeshManager::AddMesh(std::string szMapMashKey, char * szPath, char * szFileName)
{
	if (m_mapMesh.find(szMapMashKey) == m_mapMesh.end())
	{
		Mesh* pMesh = new Mesh;

		if (FAILED(pMesh->CreateMesh(szPath, szFileName)))
			return E_FAIL;

		m_mapMesh[szMapMashKey] = pMesh;
	}

	return S_OK;
}

Mesh* MeshManager::GetStaticMesh(std::string szMapMashKey)
{
	if (m_mapMesh.find(szMapMashKey) == m_mapMesh.end())
		return nullptr;
	else
		return m_mapMesh[szMapMashKey];

}

void MeshManager::Render(std::string szMapMashKey)
{
	std::map<std::string, Mesh*>::iterator iter = m_mapMesh.find(szMapMashKey);

	if (iter == m_mapMesh.end())
		return;

	iter->second->Render();
}

void MeshManager::Destroy()
{
	for each(auto p in m_mapMesh)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapMesh.clear();
}
