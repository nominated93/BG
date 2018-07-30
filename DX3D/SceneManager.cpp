#include "stdafx.h"
#include "SceneManager.h"
#include "IScene.h"
#include "GameLoading.h"
#include "LobbyScene.h"
#include "LobbyLoading.h"
#include "SceneObjMap.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_vecScene.push_back(new GameLoading());
	m_vecScene.push_back(new LobbyScene());
	m_vecScene.push_back(new LobbyLoading());
	m_vecScene.push_back(new SceneObjMap());

	SetCurrentScene(SCENE_LOADING);
}

void SceneManager::Destroy()
{
	for (auto p : m_vecScene)
	{
		SAFE_RELEASE(p);
	}
}

void SceneManager::Update()
{
	SAFE_UPDATE(m_pCurrScene);
}

void SceneManager::Render()
{
	SAFE_RENDER(m_pCurrScene);
}

void SceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrScene)
		m_pCurrScene->WndProc(hWnd, message, wParam, lParam);
}

void SceneManager::SetCurrentScene(size_t index)
{
	if (index >= m_vecScene.size()) return;

	IScene * pScene = m_vecScene[index];
	if (pScene)
	{
		pScene->Init();
		m_pCurrScene = pScene;
	}
}