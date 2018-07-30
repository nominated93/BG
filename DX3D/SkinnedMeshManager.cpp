#include "stdafx.h"
#include "SkinnedMeshManager.h"
#include "SkinnedMesh.h"

void SkinnedMeshManager::Load(std::string keyName, IN char * szFolder, IN char * szFile)
{
	SkinnedMesh* skinnedMeshTemp;
	skinnedMeshTemp = new SkinnedMesh;
	skinnedMeshTemp->Setup(szFolder, szFile);
	m_mapSkinnedMesh.insert(make_pair(keyName, skinnedMeshTemp));

}

SkinnedMesh* SkinnedMeshManager::GetSkinnedMesh(std::string keyName)
{
	m_mapSkinnedMeshIter find = m_mapSkinnedMesh.find(keyName);

	return find->second;
}

void SkinnedMeshManager::GetBoneMatrix(std::string MapKey, char* szBoneName, D3DXMATRIXA16& pMatrix)
{
	m_mapSkinnedMesh[MapKey]->FindBone(szBoneName, (ST_BONE*)m_pRoot, pMatrix);
}

SkinnedMeshManager::SkinnedMeshManager()
{
}


SkinnedMeshManager::~SkinnedMeshManager()
{
}

void SkinnedMeshManager::Destroy()
{

	for each(auto p in m_mapSkinnedMesh)
	{
		SAFE_DELETE(p.second);
	}
	m_mapSkinnedMesh.clear();

}