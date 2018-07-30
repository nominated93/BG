#pragma once

#include "UIImage.h"

class Cursor :public IDisplayObject
{
private:
	UIImage *		m_pCursorImg;
	LPD3DXSPRITE	m_pSprite;

public:
	bool m_isClick;

public:
	Cursor();
	~Cursor();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

