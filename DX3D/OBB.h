#pragma once

class OBB
{
private:
	D3DXVECTOR3 m_vOrgCenterPos;
	D3DXVECTOR3	m_vOrgAxisDir[3];

	D3DXVECTOR3	m_vCenterPos;
	D3DXVECTOR3 m_vAxisDir[3];
	float m_fAxisLen[3];
	float m_fAxisHalfLen[3];

	D3DXMATRIXA16 m_matWorldTM;

public:
	OBB();
	~OBB();

	void Init(D3DXVECTOR3 _vMin, D3DXVECTOR3 _vMax);
	void Update(D3DXMATRIXA16* pMatWorld);
	static bool IsCollision(OBB* pObb1, OBB* pObb2);
	void Render_Debug(D3DCOLOR c);
};

