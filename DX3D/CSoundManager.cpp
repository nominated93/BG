#include "stdafx.h"
#include "CSoundManager.h"


CSoundManager::CSoundManager() :
	m_pSystem(NULL)
{
}


CSoundManager::~CSoundManager()
{
	for (auto& p : m_mapSound)
	{
		p.second->pSound->release();
		delete p.second;
	}
	m_pSystem->close();
	m_pSystem->release();
}

bool CSoundManager::Init()
{
	System_Create(&m_pSystem);
	m_pSystem->init(15, FMOD_INIT_NORMAL, NULL);
	return true;
}

void CSoundManager::Destroy()
{
	delete this;
}

PSOUNDINFO CSoundManager::LoadSound(const char * fileName, bool loop, float _volume)
{
	FMOD_MODE eMode = loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;
	PSOUNDINFO pSoundInfo = new SOUNDINFO { NULL, NULL, loop, _volume };
	m_pSystem->createSound((string(SOUND_PATH) + fileName).c_str(), eMode, NULL, &pSoundInfo->pSound);

	return pSoundInfo;
}

bool CSoundManager::Play(PSOUNDINFO soundInfo)
{
	m_pSystem->update();
	m_pSystem->playSound(soundInfo->pSound, NULL, false, &(soundInfo->pChannel));
	soundInfo->pChannel->setVolume(1.0f);
	return true;
}

void CSoundManager::Stop(PSOUNDINFO soundInfo)
{
	soundInfo->pChannel->stop();
}

bool CSoundManager::Release(PSOUNDINFO soundInfo)
{
	return true;
}

void CSoundManager::Update()
{
	m_pSystem->update();
}

