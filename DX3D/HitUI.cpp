#include "stdafx.h"
#include "HitUI.h"


HitUI::HitUI()
{
}


HitUI::~HitUI()
{
}

void HitUI::Init()
{
	g_pSoundManager->AddSound("피격1", "resources/sound/hit.mp3", false, false);

}

void HitUI::Update()
{
	VecUpdate();
	RemoveLogic();
}

void HitUI::Render()
{
	VecRender();
}

void HitUI::VecUpdate()
{
	for (int i = 0; i < m_vecHitImg.size(); i++)
	{
		m_vecHitImg[i]->Update();
	}
}

void HitUI::VecRender()
{
	for (int i = 0; i < m_vecHitImg.size(); i++)
	{
		m_vecHitImg[i]->Render();
	}
}

void HitUI::AddHitUI(int iNum)
{
	switch (iNum)
	{
	case 0:
	{
		g_pSoundManager->Stop("피격1");
		g_pSoundManager->Play("피격1", 100.f);
		UIImage * pUIImg;
		pUIImg = new UIImage(m_pSprite);
		pUIImg->SetPosition(&D3DXVECTOR3(g_pRandomFunc->GetFromIntTo(50, WINSIZEX - 130), g_pRandomFunc->GetFromIntTo(50, WINSIZEY - 130), 0));
		pUIImg->SetTexture("resources/ui/피격3.png");

		pUIImg->m_AlphaBlendValue = 200;

		m_vecHitImg.push_back(pUIImg);
	}
		break;
	case 1:
	{
		g_pSoundManager->Stop("피격1");
		g_pSoundManager->Play("피격1", 100.f);
		UIImage * pUIImg;
		pUIImg = new UIImage(m_pSprite);
		pUIImg->SetPosition(&D3DXVECTOR3(g_pRandomFunc->GetFromIntTo(50, WINSIZEX - 130), g_pRandomFunc->GetFromIntTo(50, WINSIZEY - 130), 0));
		pUIImg->SetTexture("resources/ui/피격2.png");
		
		pUIImg->m_AlphaBlendValue = 200;

		m_vecHitImg.push_back(pUIImg);
	}
		break;
	case 2:
	{
		g_pSoundManager->Stop("피격1");
		g_pSoundManager->Play("피격1", 100.f);
		UIImage * pUIImg;
		pUIImg = new UIImage(m_pSprite);
		pUIImg->SetPosition(&D3DXVECTOR3(g_pRandomFunc->GetFromIntTo(50, WINSIZEX - 130), g_pRandomFunc->GetFromIntTo(50, WINSIZEY - 130), 0));
		pUIImg->SetTexture("resources/ui/피격3.png");
		
		pUIImg->m_AlphaBlendValue = 200;

		m_vecHitImg.push_back(pUIImg);
	}
		break;
	default:
		break;
	}
}

void HitUI::RemoveLogic()
{
	for (int i = 0; i < m_vecHitImg.size(); )
	{
		if (m_vecHitImg[i]->m_AlphaBlendValue <=5)
		{
			m_vecHitImg.erase(m_vecHitImg.begin()+i);
		}
		else
		{
			m_vecHitImg[i]->m_AlphaBlendValue -= 3;
			i++;
		}
	}
}


