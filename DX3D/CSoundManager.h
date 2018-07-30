#pragma once
#define g_pSoundManager CSoundManager::GetInstance()
#include "fmod/fmod.hpp"
#include <unordered_map>
#include <string>
using namespace FMOD;
using namespace std;

#define SOUND_PATH "resources/sound/"

typedef struct _tagSoungInfo
{
	Sound*		pSound;
	Channel*	pChannel;
	bool		bLoop;
	float		volume;

	~_tagSoungInfo() {
		pSound->release();
	}
} SOUNDINFO, *PSOUNDINFO;

class CSoundManager
{
	SINGLETON(CSoundManager)
private:
	System*		m_pSystem;
	unordered_map<string, PSOUNDINFO>	m_mapSound;

public:
	bool Init();
	void Destroy();
	PSOUNDINFO LoadSound(const char* fileName, bool loop = false, float _volume = 1.0f);
	bool Play(PSOUNDINFO soundInfo);
	void Stop(PSOUNDINFO soundInfo);
	bool Release(PSOUNDINFO soundInfo);
	void Update();

};

