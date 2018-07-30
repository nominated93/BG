#pragma once

#define g_pMeshManager MeshManager::GetInstance()

class Mesh;
class MeshManager
{
	SINGLETON(MeshManager);
	std::map<std::string, Mesh*> m_mapMesh;
public:

	HRESULT AddMesh(std::string szMapMashKey, char* szPath, char* szFileName);
	Mesh* GetStaticMesh(std::string szMapMashKey);
	void Render(std::string szMapMashKey);
	void Destroy();
};

