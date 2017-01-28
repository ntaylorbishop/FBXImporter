#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Animation/Motion.hpp"
#include "Engine/Renderer/Animation/Skeleton.hpp"

struct MotionBlend {
	MotionBlend(Motion* motion, float weight) : m_motion(motion), m_weight(weight), m_normalizedWeight(0.f) { }

	Motion* m_motion;
	float m_weight;
	float m_normalizedWeight;
};

class Animator {
public:
	Animator(ePlaybackType mode) : m_percentThrough(0.f) { }

	void AddMotionForBlending(Motion* motion, float evalWeight);
	void ApplyMotionToSkeleton(Skeleton* skeleton, float deltaSeconds, float evalWeight);



private:
	void CalculatePercentThrough(float deltaSeconds, MotionBlend* from, MotionBlend* to);
	void BlendAnims(Skeleton* skeleton, const std::vector<Matrix4>& from, const std::vector<Matrix4>& to, float blendWeight);

	std::vector<MotionBlend> m_motions;
	float m_percentThrough;
};