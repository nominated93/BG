#pragma once
#include "IScene.h"
#include "IUIObject.h"

class UIText;
class UIImage;
class Cursor;

class Character;
class Background;

class LobbyScene : public IScene
{
private:
	LPD3DXSPRITE			m_pSprite;
	IUIObject *				m_root;
	UIImage *				m_pBackGround;
	Cursor *				m_pCursor;
	UIText *				m_temptext;
	bool					isclick;
	char					m_startText[1024];

	Character *				m_pCharacter;

	IDirect3DTexture9*		m_BGImage;
	ID3DXSprite*			m_Sprite;
	IDirect3DDevice9*		m_Device;

	Background *			m_pBG;

public:

	LobbyScene();
	virtual ~LobbyScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void setDevice(IDirect3DDevice9* device);
	void setBGImage(std::string path);
	void Draw();
	void onLostDevice();
	void onResetDevice();
};

