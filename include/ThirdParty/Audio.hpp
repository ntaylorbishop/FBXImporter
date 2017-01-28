#ifndef INCLUDED_AUDIO
#define INCLUDED_AUDIO
#pragma once
#pragma comment( lib, "fmod/fmodex_vc" ) // Link in the fmodex_vc.lib static library

#include <string>
#include <vector>
#include <map>

#include "Engine/ErrorWarningAssert.hpp"
#include "fmod/fmod.hpp"

typedef unsigned int SoundID;
const unsigned int MISSING_SOUND_ID = 0xffffffff;

class AudioSystem {
public:
	AudioSystem();
	virtual ~AudioSystem();
	SoundID CreateOrGetSound(const std::string& soundFileName);
	void Play(SoundID soundID, float volumeLevel = 1.f);
	void Update(float deltaSeconds); // Must be called at regular intervals (e.g. every frame)

protected:
	void InitializeFMOD();
	void ValidateResult(FMOD_RESULT result);

protected:
	FMOD::System*						m_fmodSystem;
	std::map< std::string, SoundID >	m_registeredSoundIDs;
	std::vector< FMOD::Sound* >			m_registeredSounds;
};

void InitializeAudio();


#endif // INCLUDED_AUDIO
