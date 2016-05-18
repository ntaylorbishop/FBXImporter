#pragma once

#include "Engine/General/Core/GameEngine.hpp"
#include "Game/TheCamera.hpp"

class TheUI;
extern TheUI* g_theUI;

class TheUI {
public:
	//STRUCTORS
	TheUI();
	~TheUI();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

private:
	void RenderHUD() const;
	void RenderDebugText() const;
	void RenderCrosshair() const;

private:
	BitmapFont* m_squirrelFont;
};