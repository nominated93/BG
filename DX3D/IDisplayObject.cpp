#include "stdafx.h"
#include "IDisplayObject.h"


IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
}


IDisplayObject::~IDisplayObject()
{
}

void IDisplayObject::AddChild(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild.push_back(pChild);
	pChild->m_pParent = this;

}

void IDisplayObject::RemoveChild(int iNum)
{
	m_vecPChild.erase(m_vecPChild.begin() + iNum);
}

void IDisplayObject::ReleaseAll()
{
	for (auto child:m_vecPChild)
	{
		if (child) child->ReleaseAll();
	}
	Release();
}

void IDisplayObject::SetScale(D3DXVECTOR3 matS)
{
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._11 = matS.x;
	m_matWorld._22 = matS.y;

	if (m_pParent)
	{
		m_matWorld._11 *= m_pParent->GetWorldMatrix()._11;
		m_matWorld._22 *= m_pParent->GetWorldMatrix()._22;
	}
}
