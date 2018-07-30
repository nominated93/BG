#pragma once

#include "UIImage.h"

class ProgressBarManager 
{

private:
	RECT m_rcProgress;
	int m_iX, m_iY;
	float m_fWidth;

	UIImage* m_pProgressBarTop;
	UIImage* m_pProgressBarRedTop;
	UIImage* m_pProgressBarBottom;

	LPD3DXSPRITE m_pSprite;

	float m_alphaValue;

	float _currentGauge;
	float _maxGauge;

public:
	ProgressBarManager();
	~ProgressBarManager();

	void Init();
	void Release();
	void Update();
	void Render();

public:
	UIImage* GetPUIImg() { return m_pProgressBarBottom; }
	void SetGauge(float currentGauge, float maxGauge);

	void SetPosition(int x, int y);

	void SetX(int x) { m_iX = x; }
	void SetY(int y) { m_iY = y; }

	void SetAlphaValue(float alphaValue) { m_alphaValue = alphaValue; }

};

