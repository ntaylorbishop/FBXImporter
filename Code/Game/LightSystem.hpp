#pragma once

#define _USE_MATH_DEFINES

#include "Engine/General.hpp"
#include "Engine/Renderer/Light3D.hpp"

class LightSystem;
extern LightSystem* g_theLightSystem;

const RGBA LIGHTS_AMBIENT_LIGHT = RGBA(1.f, 0.f, 0.f, 0.2f);

class LightSystem {
public:
	//STRUCTORS
	LightSystem();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;


	//GETTERS SETTERS
	void SetIsLightEnabled(bool isLightEnabled);
	bool AreLightsEnabled() const;
	std::vector<Light3D> GetLights() const;

private:
	std::vector<Light3D> m_lights;

	float m_age;

	bool m_isLightEnabled;
};