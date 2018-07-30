#pragma once
#include <map>

#include "inc/fmod.hpp"


#pragma comment(lib, "lib/fmodex_vc.lib")

#define g_pSoundManager SoundManager::GetInstance()

using namespace FMOD;

#define SOUNDBUFFER 60
#define EXTRACHANNELBUFFER 60

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager 
{
private:
	SINGLETON(SoundManager)

	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;
	arrChannels _mTotalChannels;

public:
	HRESULT Init(void);
	void	Update();
	void	Release();

	HRESULT AddSound(string keyName, string soundName, bool bgm, bool loop);
	void Play(string keyName, float volume = 1.0f); // 0.0 ~ 1.0f -> 0 ~ 255
	void PlayPosition(string keyName, unsigned int position, FMOD_TIMEUNIT postype = FMOD_TIMEUNIT_MS, float volume = 1.0f);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	void SetFrequency(string keyName, float freq);
	float GetFrequency(string keyName);
	void ChangeFrequency(string keyName, float mag);
	
	void SetVolume(string keyName, float volume);

	float GetLength(string keyName);

	bool IsPlaySound(string keyName);
	bool IsPauseSound(string keyName);

};

