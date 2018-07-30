#pragma once
#include "IScene.h"
#include "IUIObject.h"

class UIImage;
class Loading;

class LobbyLoading : public IScene
{
private:
	LPD3DXSPRITE			m_pSprite;
	UIImage *				m_pBackGround;
	UIImage *				m_pLoadingbar;
	Loading *				m_pLoading;
	IUIObject *				Root;
	float					m_time;

public:
	LobbyLoading();
	~LobbyLoading();

	void Init();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	bool InitScene();
};

