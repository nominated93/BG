#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
	SINGLETON(TimeManager)
private:
	DWORD prevTime;
	DWORD deltaTime;
	float deltaTimeScene;
	float sumTime;
	int frameCnt;
	int fps;

public:
	void Update();
	float GetDeltaTime() { return deltaTimeScene; }
	float GetEllapsedTime(){ return deltaTimeScene; }
	int GetFPS() { return fps; }
};

