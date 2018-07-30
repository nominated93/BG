#pragma once
#define g_pSkinnedMeshManager SkinnedMeshManager::GetInstance()

class SkinnedMesh;

class SkinnedMeshManager
{
private:
	SINGLETON(SkinnedMeshManager);

	typedef std::map<std::string, SkinnedMesh*>::iterator m_mapSkinnedMeshIter;
	std::map<std::string, SkinnedMesh*> m_mapSkinnedMesh;

	D3DXFRAME*	m_pRoot;
public:

	void Load(std::string keyName, IN char * szFolder, IN char * szFile);
	SkinnedMesh* GetSkinnedMesh(std::string keyName);

	void GetBoneMatrix(std::string MapKey, char* szBoneName, D3DXMATRIXA16& pMatrix);

	void Destroy();
};

