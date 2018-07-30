#pragma once
class Frustum
{
private:
	D3DXVECTOR3 m_vVertex[8];
	D3DXVECTOR3 m_pos;
	D3DXPLANE m_plane[6];
public:

	Frustum();
	~Frustum();

	void Init();
	BOOL isIn(D3DXVECTOR3* pv);
	BOOL isInSphere(D3DXVECTOR3* pv, float radius);
	D3DXVECTOR3* GetPos() { return &m_pos; }
};

