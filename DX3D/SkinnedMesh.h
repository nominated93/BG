#pragma once
#include "IUnitObject.h"

class SkinnedMesh : public IUnitObject
{
protected:
	LPD3DXFRAME					m_pRoot;
	SYNTHESIZE(LPD3DXANIMATIONCONTROLLER, m_pAnimationController, AnimationController);
	LPD3DXANIMATIONSET			m_pAniSet;
	D3DXTRACK_DESC				m_stTrackDesc;

	float		m_fPassedBlendTime;
	float		m_fBlendTime;
	bool		m_isBlend;

	SYNTHESIZE(D3DXVECTOR3, m_vMin, Min);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);

public:
	SkinnedMesh();
	~SkinnedMesh();

	void Setup(IN char* szFolder, IN char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_World);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	// animation
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	LPD3DXFRAME GetRoot() { return m_pRoot; }

	void FindBone(IN char* szBoneName, ST_BONE* pBone, OUT D3DXMATRIXA16& pMatrix);

	// Inherited via IUnitObject
	virtual void Init() override;
	virtual void Render() override;

	void Render(LPD3DXFRAME pFrame);
};