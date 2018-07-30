#include "stdafx.h"
#include "UIButton.h"


UIButton::UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite, int uiTag)
	:IUIObject(pSprite, uiTag), m_pDelegate(pDelegate), m_buttonState(NORMAL)
{
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
	IUIObject::Update();

	RECT rect;
	GetFinalRect(&rect);

	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	//마우스 포인터가 영역 안에 있을 때
	if (PtInRect(&rect, mousePoint))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_buttonState == MOUSEOVER)
			{
				m_buttonState = SELECTED;
			}
		}
		else
		{
			if (m_buttonState == SELECTED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSEOVER;
		}
	}
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{

		}
		else
		{
			m_buttonState = NORMAL;
		}
	}

}

void UIButton::Render()
{
	if (m_aTexture[m_buttonState])
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);

		m_pSprite->Draw(m_aTexture[m_buttonState],
			&rect,
			&D3DXVECTOR3(m_info.Width / 2.0f, m_info.Height / 2.0f, 0),
			&D3DXVECTOR3(m_combinedPos.x + m_info.Width / 2.0f, m_combinedPos.y + m_info.Height / 2.0f, 0),
			D3DCOLOR_ARGB(200, 255, 255, 255));
	}

	//IUIObject::Render();
	m_pSprite->End();
}

void UIButton::SetTexture(string normal, string mouseover, string seleted)
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);


	ZeroMemory(&m_info, sizeof(D3DXIMAGE_INFO));

	m_aTexture[NORMAL] = g_pTextureManager->GetTexture(normal);
	D3DXCreateTextureFromFileEx(
		g_pDevice,
		normal.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_info,
		NULL,
		&m_aTexture[NORMAL]);

	
	m_aTexture[MOUSEOVER] = g_pTextureManager->GetTexture(mouseover);

	D3DXCreateTextureFromFileEx(
		g_pDevice,
		mouseover.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_info,
		NULL,
		&m_aTexture[MOUSEOVER]);


	m_aTexture[SELECTED] = g_pTextureManager->GetTexture(seleted);

	D3DXCreateTextureFromFileEx(
		g_pDevice,
		seleted.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_info,
		NULL,
		&m_aTexture[SELECTED]);

	D3DXGetImageInfoFromFileA(normal.c_str(), &m_info);
	m_size.x = m_info.Width;
	m_size.y = m_info.Height;
}

void UIButton::SetText(LPD3DXFONT font, LPCTSTR text)
{
}
