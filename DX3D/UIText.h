#pragma once

#include "IUIObject.h"

class UIText :
	public IUIObject
{
public:

	LPD3DXFONT	m_pFont;
	LPCTSTR		m_text;
	//char		m_text[1024];
	DWORD		m_drawTextFormat;

	//UIText(LPD3DXFONT pFont, LPD3DXSPRITE pSprite, int uiTag = -1);
	UIText(LPD3DXFONT pFont, LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~UIText();

	virtual void Render() override;
	//void SetText(char* &text) { strcat_s(m_text, text); }
};

