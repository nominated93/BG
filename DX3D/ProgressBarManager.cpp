#include "stdafx.h"
#include "ProgressBarManager.h"


ProgressBarManager::ProgressBarManager()
{
	m_alphaValue = 70;
}


ProgressBarManager::~ProgressBarManager()
{
	m_pProgressBarTop->Release();
	m_pProgressBarBottom->Release();
}

void ProgressBarManager::Init()
{
	
	m_pProgressBarTop = new UIImage(m_pSprite);
	m_pProgressBarTop->m_AlphaBlendValue = m_alphaValue;
	m_pProgressBarTop->SetTexture("resources/ui/HpBarUp.bmp"); 

	m_pProgressBarRedTop = new UIImage(m_pSprite);
	m_pProgressBarRedTop->m_AlphaBlendValue = m_alphaValue;
	m_pProgressBarRedTop->SetTexture("resources/ui/HpBarRed.png");

	m_pProgressBarBottom = new UIImage(m_pSprite);
	m_pProgressBarBottom->m_AlphaBlendValue = m_alphaValue;
	m_pProgressBarBottom->SetTexture("resources/ui/HpBarDown.bmp");
	
	m_fWidth = m_pProgressBarTop->GetInfo().Width;

}

void ProgressBarManager::Release()
{
	
}

void ProgressBarManager::Update()
{
	SetRect(&m_rcProgress, m_iX, m_iY, m_pProgressBarTop->GetInfo().Width, m_pProgressBarTop->GetInfo().Height);
	
	D3DXIMAGE_INFO info = m_pProgressBarTop->GetInfo();
	info.Width = m_fWidth;
	m_pProgressBarTop->SetInfo(info);
	m_pProgressBarRedTop->SetInfo(info);

	m_pProgressBarTop->m_AlphaBlendValue = m_alphaValue;
	m_pProgressBarRedTop->m_AlphaBlendValue = m_alphaValue;
	m_pProgressBarBottom->m_AlphaBlendValue = m_alphaValue;

	if (_currentGauge >= _maxGauge)
	{
		m_alphaValue = 70;
	}
	else if (_currentGauge < _maxGauge)
	{
		m_alphaValue = 100;
	}

	

	m_pProgressBarTop->Update();
	m_pProgressBarRedTop->Update();
	m_pProgressBarBottom->Update();
}

void ProgressBarManager::Render()
{
	m_pProgressBarBottom->Render();

	if (_currentGauge <= _maxGauge / 2)
	{
		m_pProgressBarRedTop->Render();
	}
	else
	{
		m_pProgressBarTop->Render();
	}
}


void ProgressBarManager::SetGauge(float currentGauge, float maxGauge)
{
	_currentGauge = currentGauge;
	_maxGauge = maxGauge;

	if(_currentGauge > 0 && _maxGauge > _currentGauge)
		m_fWidth = (_currentGauge / _maxGauge) * m_pProgressBarBottom->GetInfo().Width;

}

void ProgressBarManager::SetPosition(int x, int y)
{
	m_iX = x;
	m_iY = y;

	SetRect(&m_rcProgress, x, y, m_pProgressBarBottom->GetInfo().Width, m_pProgressBarBottom->GetInfo().Height);

	
	m_pProgressBarBottom->SetPosition(&D3DXVECTOR3(x, y, 0));
	m_pProgressBarTop->SetPosition(&D3DXVECTOR3(x, y, 0));
	m_pProgressBarRedTop->SetPosition(&D3DXVECTOR3(x, y, 0));
}
