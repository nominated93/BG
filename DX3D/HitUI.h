#pragma once

#include "UIImage.h"

class HitUI : public IDisplayObject
{
private:
	LPD3DXSPRITE	m_pSprite;

private:
	vector<UIImage*> m_vecHitImg;

public:
	HitUI();
	~HitUI();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	void VecUpdate();
	void VecRender();

public:
	void AddHitUI(int iNum);
	void RemoveLogic();

public:

	vector<UIImage*>*	GetPVecHitImg() { return &m_vecHitImg; }

};

