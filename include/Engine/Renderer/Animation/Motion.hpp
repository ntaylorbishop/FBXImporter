#pragma once

#include <cmath>

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Math/Matrix4.hpp"
#include "Engine/General/Utils/FileUtils/FileBinaryReader.hpp"
#include "Engine/General/Utils/FileUtils/FileBinaryWriter.hpp"
#include "Engine/Renderer/Animation/Skeleton.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//ENUMS
//---------------------------------------------------------------------------------------------------------------------------
enum ePlaybackType {
	PLAYBACK_CLAMP = 0,
	PLAYBACK_LOOP,
	PLAYBACK_PINGPONG
};

class Motion {
public:
	Motion(String name, float timeSpan, float framerate);
	Motion(String name, float timeSpan, float framerate, Skeleton* skeleton);
	~Motion() { }

	void GetFrameIndicesWithBlend(uint32_t& outFrameIdx0, uint32_t& outFrameIdx1, float& outBlend, float inTime);
	void ApplyMotionToSkeleton(Skeleton* skeleton, float time);
	std::vector<Matrix4>* GetJointKeyframes(int jointIdx);

	void SetPlaybackType(ePlaybackType type) { m_playbackType = type; }
	ePlaybackType GetPlaybackType() { return m_playbackType; }

	//IO
	static void WriteAnimToFile(Motion* motion, const String& filename);
	static Motion* ReadAnimFromFile(const String& filename);

	//FOR BLENDING
	void GetJointTransformForWeightsAtKeyframe(Skeleton* skeleton, float blendWeight, std::vector<Matrix4>& matsForJoints);


public:
	std::vector<std::vector<Matrix4>> m_keyframes;

public:
	String m_name;
	uint32_t m_frameCount;
	float m_totalLengthSeconds;
	float m_frameRate;
	float m_frameTime;
	Skeleton* m_skeleton;

	ePlaybackType m_playbackType;
};