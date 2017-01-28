#pragma once

#include "Engine/Renderer/Sprites/Spritesheet.hpp"
#include "Engine/Renderer/General/Texture.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Math/Vector2.hpp"

enum eAnimMode {
	ANIM_MODE_PLAY_TO_END = 0,
	ANIM_MODE_LOOPING,
	ANIM_MODE_PING_PONG,
	NUM_ANIM_SPRITE_MODES
};

class SpriteAnim {
public:
	SpriteAnim();
	SpriteAnim(const SpriteSheet* spriteSheet, float durationSeconds, eAnimMode spriteAnimMode, int spriteStartIndex, int spriteEndIndex);

	void Update(float deltaSeconds);
	AABB2 getCurrentTexCoords() const;
	const Texture* getTexture();
	const SpriteSheet* getSpriteSheet() const;
	void Pause();
	void Resume();
	void Reset();
	bool isFinished() const;
	bool isPlaying() const;
	float getDurationSeconds() const;
	float getSecondsElapsed() const;
	float getSecondsRemaining() const;
	float getFractionElapsed() const;
	float getFractionRemaining() const;
	void setSecondsElapsed(float secondsElapsed);
	void setFractionElapsed(float fractionElapsed);

private:
	const SpriteSheet* m_spriteSheet;
	float m_durationSeconds;
	eAnimMode m_animMode;
	int m_spriteStartIndex;
	int m_spriteEndIndex;
	int m_currIndex;

	bool m_isPlaying;
	float m_age;
};

/*
Enum {
Playtoend
Looping
Pingpong
Num sprite anim modes
}

SpriteAnim(spritesheet, durationseconds, spriteanimmode, startindex, endindex)

Update
AABB2 getcurrenttexcoords
Texture gettexture
Pause
Resume
Reset
Isfinished
Isplaying
Getdurationseconds
Getsecondselapsed
Getsecondsremaining
Getfractionelapsed
Getfractionremaining
Setsecondselapsed
setfractionelapsed
*/