#include "stdafx.h"
//#include "FireParticle.h"
//
//
//FireParticle::FireParticle()
//{
//}
//
//FireParticle::FireParticle(D3DXVECTOR3 * origin, int numParticles)
//{
//	_pos = *origin;
//	_size = 0.4f;
//	_vbSize = 16;
//	_vbOffset = 0;
//	_vbBatchSize = 512;
//
//	Particle::Init(NULL);
//
//
//	for (int i = 0; i < numParticles; i++)
//	{
//		AddParticle();
//	}
//}
//
//
//FireParticle::~FireParticle()
//{
//}
//
//void FireParticle::ResetParticle(sAttribute * attribute)
//{
//	attribute->isAlive = true;
//	attribute->position = _pos;
//
//	D3DXVECTOR3 vMin = D3DXVECTOR3(-0.2f, -0.2f, -0.2f);
//	D3DXVECTOR3 vMax = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
//
//	Particle::GetRandomVector(&attribute->velocity, &vMin, &vMax);
//
//	//구체를 만들기 위한 정규화
//	D3DXVec3Normalize(&attribute->_velocity, &attribute->_velocity);
//
//	attribute->_velocity *= 100.0f;
//
//	attribute->_color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//
//	attribute->_age = 0.0f;
//	attribute->_lifeTime = 0.01f;
//}
//
//void FireParticle::Update(float fTimeDelta)
//{
//	std::list<ST_Particle*>::iterator iter;
//	for (iter = m_lParticles.begin(); iter != m_lParticles.end(); iter++)
//	{
//		//생존한 파티클만 갱신한다
//		if ((*iter)->_isAlive)
//		{
//			(*iter)->_position += (*iter)->_velocity * fTimeDelta;
//			(*iter)->_age += fTimeDelta;
//
//			if ((*iter)->_age > (*iter)->_lifeTime)
//			{
//				(*iter)->_isAlive = false;
//				resetParticle((*iter));
//			}
//
//		}
//	}
//}
//
//void FireParticle::PreRender()
//{
//	Particle::PreRender();
//
//	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
//	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//	//z 버퍼 읽기는 가능하지만 쓰기는 혀용되지 않는다
//	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
//}
//
//void FireParticle::PostRender()
//{
//	Particle::PostRender();
//	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
//}
