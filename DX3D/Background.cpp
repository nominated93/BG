#include "stdafx.h"
#include "Background.h"

Background::Background(LPCSTR top, LPCSTR bottom, LPCSTR left, LPCSTR right, LPCSTR front, LPCSTR back)
{
	D3DXCreateTextureFromFile(g_pDevice, top, &mTex[0]);
	D3DXCreateTextureFromFile(g_pDevice, bottom, &mTex[1]);
	D3DXCreateTextureFromFile(g_pDevice, left, &mTex[2]);
	D3DXCreateTextureFromFile(g_pDevice, right, &mTex[3]);
	D3DXCreateTextureFromFile(g_pDevice, front, &mTex[4]);
	D3DXCreateTextureFromFile(g_pDevice, back, &mTex[5]);


	VERTEX_PNT* pv;

	for (int i = 0; i<6; i++)
	{
		if (FAILED(g_pDevice->CreateVertexBuffer(sizeof(VERTEX_PNT) * 4, 0, VERTEX_PNT::FVF, D3DPOOL_DEFAULT, &mVtx[i], NULL))) return;
	}
	//top
	if (FAILED(mVtx[0]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	mVtx[0]->Unlock();
	//bottom
	if (FAILED(mVtx[1]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[1]->Unlock();
	//left
	if (FAILED(mVtx[2]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[2]->Unlock();
	//right
	if (FAILED(mVtx[3]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[3]->Unlock();
	//front
	if (FAILED(mVtx[4]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[4]->Unlock();
	//back
	if (FAILED(mVtx[5]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[5]->Unlock();

	for (int i = 0; i<6; i++)
	{
		if (FAILED(g_pDevice->CreateIndexBuffer(sizeof(CINDEX) * 12, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIdx[i], NULL))) return;
	}

	CINDEX* iv;

	for (int i = 0; i<6; i++)
	{
		if (FAILED(mIdx[i]->Lock(0, 0, (void**)&iv, 0))) return;
		Set_Idx(iv[0], 0, 1, 2);
		Set_Idx(iv[1], 2, 1, 3);
		mIdx[i]->Unlock();
	}

	return;
}

Background::~Background()
{
	for (int i = 0; i<6; i++)
	{
		SAFE_RELEASE(mTex[i]);
		SAFE_RELEASE(mVtx[i]);
		SAFE_RELEASE(mIdx[i]);
	}
}

void Background::Render()
{

	if (!mVtx || !mIdx) return;

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);



	//D3DXVECTOR3 vPos = g_pCamera->m_eye;

	D3DXMATRIX matWrd, matS, matT;
	D3DXMatrixIdentity(&matWrd);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, 130.0f, 130.0f, 130.0f);
	D3DXMatrixTranslation(&matT, 0, 20, 0);

	matWrd = matS;
	matWrd = matS * matT;

	g_pDevice->SetTransform(D3DTS_WORLD, &matWrd);
	//D3DXMATRIXA16 matView, matProj;

	//D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.f, 0.f, -20.f), &D3DXVECTOR3(0.f, 4.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f));
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.f, WINSIZEX / (float)WINSIZEY, 1.f, 1000.f);

	//g_pDevice->SetTransform(D3DTS_VIEW, &matView);
	//g_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	for (int i = 0; i<6; i++)
	{
		g_pDevice->SetTexture(0, (mTex[i]) ? mTex[i] : NULL);
		g_pDevice->SetStreamSource(0, mVtx[i], 0, sizeof(VERTEX_PNT));
		g_pDevice->SetFVF(VERTEX_PNT::FVF);
		g_pDevice->SetIndices(mIdx[i]);
		g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}

	D3DXMatrixIdentity(&matWrd);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWrd);
	
	g_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

void Background::Set_Vtx3D_Tex(VERTEX_PNT & ct, D3DXVECTOR3 p, D3DXVECTOR3 n, float tu, float tv)
{
	ct.p = p;
	ct.n = n;
	ct.t = D3DXVECTOR2(tu, tv);
}

void Background::Set_Idx(CINDEX & ci, WORD _0, WORD _1, WORD _2)
{
	ci._0 = _0; ci._1 = _1;	ci._2 = _2;
}
//
//void Background::Init()
//{
//}
//
//void Background::Update()
//{
//}
