#include "stdafx.h"
#include "SoundManager.h"
#include "inc/fmod.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{

}

HRESULT SoundManager::Init()
{
	//FMOD 사운드 엔진을 사용하겠다고 선언
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	return S_OK;
}

void SoundManager::Release()
{

}

void SoundManager::Update()
{

}


HRESULT SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (_mTotalSounds.size() != _mTotalChannels.size()) return E_FAIL;

	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
	_mTotalChannels.insert(make_pair(keyName, &_channel[_mTotalChannels.size()]));

	return S_OK;
}

void SoundManager::Play(string keyName, float volume)// 0.0 ~ 1.0f -> 0 ~ 255
{
	/*arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}*/

	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		_system->playSound(FMOD_CHANNEL_FREE, *_mTotalSounds.find(keyName)->second, false, _mTotalChannels.find(keyName)->second);

		(*_mTotalChannels.find(keyName)->second)->setVolume(volume);
	}
}

void SoundManager::PlayPosition(string keyName, unsigned int position, FMOD_TIMEUNIT postype, float volume)
{
	/*arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			_channel[count]->setPosition(position, postype);
			_channel[count]->setVolume(volume);
			break;
		}
	}*/

	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		_system->playSound(FMOD_CHANNEL_FREE, *_mTotalSounds.find(keyName)->second, false, _mTotalChannels.find(keyName)->second);
		(*_mTotalChannels.find(keyName)->second)->setPosition(position, postype);
		(*_mTotalChannels.find(keyName)->second)->setVolume(volume);
	}

}

void SoundManager::Stop(string keyName)
{
	/*arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}*/

	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		(*_mTotalChannels.find(keyName)->second)->stop();
	}
}

void SoundManager::Pause(string keyName)
{
	/*arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}*/

	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		(*_mTotalChannels.find(keyName)->second)->setPaused(true);
	}
}

void SoundManager::Resume(string keyName)
{
	/*arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}*/

	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		(*_mTotalChannels.find(keyName)->second)->setPaused(false);
	}
}

void SoundManager::SetFrequency(string keyName, float freq)
{
	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		(*_mTotalChannels.find(keyName)->second)->setFrequency(freq);
	}
}

float SoundManager::GetFrequency(string keyName)
{
	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		float freq;
		(*_mTotalChannels.find(keyName)->second)->getFrequency(&freq);
		return freq;
	}
	
	return 0.0f;
}

void SoundManager::ChangeFrequency(string keyName, float mag)
{
	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		float freq;
		(*_mTotalChannels.find(keyName)->second)->getFrequency(&freq);
		(*_mTotalChannels.find(keyName)->second)->setFrequency(freq * mag);
	}
}

void SoundManager::SetVolume(string keyName, float volume)
{
	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		(*_mTotalChannels.find(keyName)->second)->setVolume(volume);
	}
}

float SoundManager::GetLength(string keyName)
{
	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		unsigned int n;
		(*_mTotalSounds.find(keyName)->second)->getLength(&n, FMOD_TIMEUNIT_MS);
		return static_cast<float>(n) / 1000;
	}
	return 0;
}

bool SoundManager::IsPlaySound(string keyName)
{
	bool isPlay = false;
	/*arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}*/

	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		(*_mTotalChannels.find(keyName)->second)->isPlaying(&isPlay);
	}

	return isPlay;
}

bool SoundManager::IsPauseSound(string keyName)
{
	bool isPause;
	/*arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}*/

	if (_mTotalSounds.find(keyName) != _mTotalSounds.end())
	{
		(*_mTotalChannels.find(keyName)->second)->getPaused(&isPause);
	}

	return isPause;
}

