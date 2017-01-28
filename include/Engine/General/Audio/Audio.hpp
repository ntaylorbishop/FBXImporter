#pragma once

#include <string>
#include <vector>
#include <map>

#include "Engine/General/Utils/ErrorWarningAssert.hpp"
#include "ThirdParty/fmod/fmod.hpp"

typedef void* AudioChannelHandle;
typedef unsigned int SoundID;
const unsigned int MISSING_SOUND_ID = 0xffffffff;

class AudioSystem {
public:
	AudioSystem();
	virtual ~AudioSystem();

	SoundID CreateOrGetSound(const std::string& soundFileName);

	AudioChannelHandle Play(SoundID soundID, float volumeLevel = 1.f);
	AudioChannelHandle PlayLoop(SoundID soundID, float volumeLevel = 1.f);

	void StopChannel(AudioChannelHandle channel);
	void PauseChannel(AudioChannelHandle channel);
	void UnpauseChannel(AudioChannelHandle channel);
	void ChangeVolumeOfChannel(AudioChannelHandle channel, float volume);

	void Update(float deltaSeconds); // Must be called at regular intervals (e.g. every frame)

protected:
	void InitializeFMOD();
	void ValidateResult(FMOD_RESULT result);

protected:
	FMOD::System*						m_fmodSystem;
	std::map< std::string, SoundID >	m_registeredSoundIDs;
	std::vector< FMOD::Sound* >			m_registeredSounds;
	std::map< SoundID, AudioChannelHandle> m_soundIDChannels;
};