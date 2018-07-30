#pragma once

class DrawingGroup;

class ObjLoader
{
public:
	vector<VERTEX_PNT>		vecPNT;

	string					m_filePath;
	map<string, MTLTEX*>	m_mapMtlTex;

	ObjLoader();
	~ObjLoader();

	// OUT -> Load된 값을 거기에 넣어주겠다
	// 이거 안씀
	void Load(const char* filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<DrawingGroup*> &vecGroup);
	void LoadSurface(const char* fullpath, D3DXMATRIXA16* pMat, OUT vector<D3DXVECTOR3> &vecVertex);

	// .Obj 파일을 로드하는 메서드
	// filePath = 경로, fileName = 파일이름, pMat = 월드매트릭스, vecGroup = 실제로 OUT될 버텍스 벡터
	LPD3DXMESH LoadMesh(const char* filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<MTLTEX*> &vecMtlTex);

	// mtl라이브러리 호출
	void LoadMtlLib(string fullpath);
	bool CompareStr(char* str1, const char* str2);

	void CreateSurface(OUT vector<D3DXVECTOR3> &vecVertex);
};

