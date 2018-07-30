#include "stdafx.h"
#include "DrawingGroup.h"


DrawingGroup::DrawingGroup()
{
	m_pVB = NULL;
	m_MtlTex = NULL;
}


DrawingGroup::~DrawingGroup()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_MtlTex);
}

void DrawingGroup::SetVertexBuffer(const vector<VERTEX_PNT>& vec)
{
	//렌더링 무슨 차이인지 알아보기!
	//D3DPOOL_SYSTEMMEM : 시스템 멤에 저장
	//D3DPOOL_MANAGED : 시스템 멤이든 램이든 알아서 와리가리침(램이 더 느리댄다, 그래픽 카드에 넣어두는게 좋댄다)
	//D3DPOOL_DEFAULT : 그래픽 카드에 저장
	//버퍼 세팅하기, 이 코드가 의미하는 것은 무엇일까!?
	//디폴트가 매니지드보다 속도가 더 빠름
	//첫번째 주석 의견추가: 시스템 메모리 = RAM으로 이해하시는게 이해하는데 도움될것 같습니다
	g_pDevice->CreateVertexBuffer(vec.size() * sizeof(VERTEX_PNT), 0, VERTEX_PNT::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);
	
	m_numTri = vec.size() / 3;

	VERTEX_PNT * pVertices;
	m_pVB->Lock(0, 0, (LPVOID *)&pVertices, 0);
	memcpy(pVertices, &vec[0], vec.size() * sizeof(VERTEX_PNT));
	m_pVB->Unlock();
}

void DrawingGroup::Render()
{
	g_pDevice->SetTexture(0, m_MtlTex->pTexture);
	g_pDevice->SetMaterial(&m_MtlTex->material);
	g_pDevice->SetFVF(VERTEX_PNT::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PNT));
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_numTri);
}
