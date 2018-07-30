#pragma once
#include "IUnitObject.h"

class SkinnedMesh;
class OBB;

class Monster : public IUnitObject
{

private:
	SkinnedMesh * m_pSkinnedMesh;


	LPD3DXMESH      m_pMesh;
	string			m_szCurrentFile;
	ePlayerState	m_eState;
	LPD3DXSPRITE	m_pSprite;

	OBB*			m_pOBB;

public:
	Monster();
	~Monster();

	void Init();
	void Init(char* fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Update();
	void Render();
	void SetAnimationIndexBlend(int nIndex);

public:

};