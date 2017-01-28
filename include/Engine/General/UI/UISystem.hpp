#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/UI/UIComponent.hpp"

class UISystem;
extern UISystem* g_theUISystem;

class UISystem {
public:
	//STRUCTORS
	UISystem();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	//REGISTRATION
	void RegisterComponent(UIComponent* component);

private:
	std::vector<UIComponent*> m_components;
};