#pragma once
#include "BaseObject.h"
class DrawingGroup :
	public BaseObject
{
private:
	//한번 그릴 때 필요한 최소한의 변수들
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	size_t					m_numTri;
	MTLTEX *				m_MtlTex;


public:
	DrawingGroup();
	~DrawingGroup();

	void SetMtlTex(MTLTEX * p) { m_MtlTex = p; }
	void SetVertexBuffer(const vector<VERTEX_PNT> & vec);
	void Render();
};

