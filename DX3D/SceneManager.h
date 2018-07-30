#pragma once

#define g_pSceneManager SceneManager::GetInstance()

class IScene;//씬의 base클래스를 하나 추가해주자.

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager * GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}
	
	vector<IScene*>  m_vecScene;

	IScene* m_pCurrScene;

	void Init();
	void Destroy();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetCurrentScene(size_t index);

};

