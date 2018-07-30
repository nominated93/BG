#pragma once

#include "UIImage.h"

class UIButton;
class IUIObject;

class Minimap : public IDisplayObject
{
private:
	LPD3DXSPRITE	m_pSprite;
	IUIObject *		m_pMinimap;
	IUIObject *		m_pIcon;
	UIImage *		pImage;
	UIImage *		pMapIcon;
	RECT			rc;
	D3DXVECTOR3		playerPos;

public:
	Minimap();
	~Minimap();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

