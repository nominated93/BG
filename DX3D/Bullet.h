#pragma once
#include "IDisplayObject.h"

class Camera;

class Bullet : public IDisplayObject
{
private:
	SYNTHESIZE(float, m_fDamage, Damage);
	SYNTHESIZE(float, m_fSpeed, Speed);
	SYNTHESIZE(float, m_fRange, Range);
	SYNTHESIZE(bool, m_isAlive, isAlive);
	D3DXVECTOR3 firstPos;

	LPD3DXMESH	m_pSphere;

public:
	void Init(float damage, float speed, float range, D3DXVECTOR3* pos, D3DXVECTOR3* dir);
	void Update();
	void Render();
	Bullet();
	~Bullet();

	D3DXVECTOR3 GetStartPosition() { return firstPos; }

	// Inherited via IDisplayObject
	virtual void Init() override;
};

