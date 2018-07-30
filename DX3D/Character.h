#pragma once
#include "IUnitObject.h"
#include "IUIObject.h"

class SkinnedMesh;

class UIImage;

class Character : public IUnitObject
{
	SkinnedMesh*			m_pSkinnedMesh;

	LPD3DXSPRITE			m_pSprite;
	IUIObject *				m_root;
	UIImage *				m_pBackGround;

public:
	Character();
	~Character();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

