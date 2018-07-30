#include "stdafx.h"
#include "UIImage.h"


UIImage::UIImage(LPD3DXSPRITE pSprite, int uiTag)
	: IUIObject(pSprite, uiTag)
	, m_pTex(NULL)
{
	//m_pSprite = pSprite;
}

UIImage::~UIImage()
{
}

void UIImage::Update()
{
	IUIObject::Update();
}

void UIImage::Render()
{
	if (m_pTex)
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_info.Width, m_info.Height);

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMatrixIdentity(&mat);
		m_pSprite->SetTransform(&mat);
		m_pSprite->Draw(m_pTex,
			&rect,//&rc,
			&D3DXVECTOR3(m_info.Width / 2.0f, m_info.Height / 2.0f, 0),
			&D3DXVECTOR3(m_combinedPos.x + m_info.Width / 2.0f, m_combinedPos.y + m_info.Height / 2.0f, m_combinedPos.z),
			D3DCOLOR_ARGB(m_AlphaBlendValue, 255, 255, 255));
	}

	IUIObject::Render();
	m_pSprite->End();

	//Debug->AddText("pos : ");
	//Debug->AddText(m_combinedPos);
	//Debug->EndLine();
}

void UIImage::SetTexture(string fullPath)
{
	
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	ZeroMemory(&m_info, sizeof(D3DXIMAGE_INFO));

	D3DXCreateTextureFromFileEx(
		g_pDevice,
		fullPath.c_str(),
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
		&m_pTex);
}
