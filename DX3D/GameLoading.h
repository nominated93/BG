#pragma once
#include "IScene.h"

class IUIObject;
class UIImage;
class Loading;

class GameLoading : public IScene
{
private:
	LPD3DXSPRITE			m_pSprite;
	UIImage *				m_pBackGround;
	UIImage *				m_pLoadingbar;
	Loading *				m_pLoading;
	IUIObject *				Root;
	float					m_time;

public:
	GameLoading();
	~GameLoading();

	void Init();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

