#pragma once

class AseObject;

class AseLoader
{
private:
	std::ifstream m_fin;
	char m_szToken[512];
	vector<D3DMATERIAL9> m_vecMtl;
	vector<string> m_vecTexName;
	//이름으로 맵에 저장했다가, 찾아서 사용하기 위한 용도
	//부위 하나 하나 마다 오브젝트로 생성된 객체 임을 유의하자!
	map<string, AseObject *> m_mapAseObject;

	//ChildWTM = ChildLTM x ParentWTM
	/*
	노드의 월드 행렬 = 노드의 지역행렬 (Local Matrix) * 부모의 월드 행렬(Parnet World Matrix)
	노드의 지역 행렬 = 노드의 월드 행렬 * 부모의 월드행렬의 역행렬
	*/

public:
	AseLoader();
	~AseLoader();

	//파일보면 띄어쓰기가 너무 많아
	//단어 단위로 묶어 쓰는 용도의 함수가 필요함.(토큰은 파싱해서 사용하는 용도)
	AseObject * Load(const char * fullPath , OUT ASE_SCENE * pScene);
	char * GetToken();
	int GetTokenAsInt();
	float GetTokenAsFloat();
	bool CompareStr(char * str1, const char * str2);

	void ProcessSCENE(OUT ASE_SCENE * pScene);

	void ProcessMATERIAL_LIST();
	void ProcessMATERIAL(int index);
	void ProcessMAP_DIFFUSE(int index);
	AseObject * ProcessGEOMOBJECT(OUT AseObject * & pObj);
	void ProcessNODE_TM(OUT AseObject * & pObj);
	void ProcessMESH(OUT AseObject * &pObj);
	void ProcessMESH_VERTEX_LIST(OUT vector<D3DXVECTOR3> & vecP);
	void ProcessMESH_FACE_LIST(IN vector<D3DXVECTOR3> & vecP, OUT vector<VERTEX_PNT> & vecVertex);

	void ProcessMESH_TVERTLIST(OUT vector<D3DXVECTOR2> & vecT);
	void ProcessMESH_TFACELIST(IN vector<D3DXVECTOR2> & vecT, OUT vector<VERTEX_PNT > & vecVertex);
	void ProcessMESH_NORMALS(OUT vector<VERTEX_PNT> & vecVertex);
	void ProcessTM_ANIMATION(OUT AseObject *& pObj);
	void ProcessPOS_TRACK(OUT AseObject * & pObj);
	void ProcessROT_TRACK(OUT AseObject * & pObj);
};

