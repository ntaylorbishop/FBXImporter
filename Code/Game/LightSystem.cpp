#include "Game/LightSystem.hpp"
#include "Game/TheCamera.hpp"

LightSystem* g_theLightSystem = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
LightSystem::LightSystem() 
	: m_age(0.f)
{
	//m_lights.push_back(Light3D(Vector3(0.f, -3.f, 0.f), RGBA::WHITE, 10.f));
	//LOCAL POINT LIGHT
	m_lights.push_back(Light3D(Vector3(0.f, -3.f, 5.f), RGBA::WHITE, 30.f));

/*
	//LOCAL CONE LIGHT
	m_lights.push_back(Light3D(Vector3(5.f, 5.f, 5.f)
		, Vector3(0.f, 0.f, -1.f)
		, RGBA::RED
		, 0.f, 10.f
		, 1.f, 0.f
		, 0.1f, 0.5f
		, 0.f, 4.f
	));*/

	//GLOBAL CONE LIGHT
	m_lights.push_back(Light3D(Vector3(5.f, 20.f, 20.f)
		, Vector3(0.f, -1.f, -1.f)
		, RGBA::WHITE
		, 0.f, 1.f
		, 0.3f, 0.3f
		, 0.1f, 0.5f
		, 0.f, 1.f
		));

/*
	//GlOBAL POINT LIGHT
	m_lights.push_back(
		Light3D
			( Vector3(5.f, -80.f, 80.f)
			, Vector3(0.f, 0.f, -1.f)
			, RGBA::BLUE
			, 10.f, 15.f
			, 1.f, 1.f, 1.f
			, 1.f, -1.f
			, 1.f, 1.f
		)
	);*/
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void LightSystem::Update(float deltaSeconds) {
	m_age += deltaSeconds;

	m_lights[0].SetPosition(g_theCamera->m_position);
}
void LightSystem::Render() const {
	if (m_isLightEnabled) {
		for (unsigned int i = 1; i < m_lights.size(); i++) {
			g_theDebugRenderer->DrawDebugSphere(m_lights[i].GetPosition(), 0.5f, m_lights[i].GetColor(), DEBUG_DRAW_DEPTH_TEST_ON);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//GETTERS SETTERS
//---------------------------------------------------------------------------------------------------------------------------
void LightSystem::SetIsLightEnabled(bool isLightEnabled) {
	m_isLightEnabled = isLightEnabled;
}
bool LightSystem::AreLightsEnabled() const {
	return m_isLightEnabled;
}

std::vector<Light3D> LightSystem::GetLights() const {
	return m_lights;
}