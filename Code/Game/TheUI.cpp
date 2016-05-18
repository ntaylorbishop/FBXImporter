#include "Game/TheUI.hpp"
#include "Game/TheGame.hpp"

TheUI* g_theUI = nullptr;

//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
TheUI::TheUI() {
	m_squirrelFont = BitmapFont::CreateOrGetFont("SquirrelFixedFont");
}
TheUI::~TheUI() {

}

//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheUI::Update(float deltaSeconds) {
	deltaSeconds = 0;
}
void TheUI::Render() const {
	g_theRenderer->SetOrtho2D(Vector2(0.f, 0.f), Vector2(1600.f, 900.f));

	RenderHUD();
	RenderDebugText();
	RenderCrosshair();
}

//HUD
//---------------------------------------------------------------------------------------------------------------------------
void TheUI::RenderHUD() const {
	//Does nothing for right now
}
void TheUI::RenderDebugText() const {
	IntVector2 mousePos = g_theInputSystem->GetCursorPosition();
	String mousePosStr = "X: " + to_string(mousePos.x) + " Y: " + to_string(mousePos.y);

	String blendWeightStr = to_string(g_theGame->m_blendWeight);
	m_squirrelFont->DrawText2D(Vector2(1350.f, 50.f), blendWeightStr, 20.f, RGBA::YELLOW, NULL);
}

void TheUI::RenderCrosshair() const {
	g_theRenderer->BlendMode(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	g_theRenderer->DrawLine(Vector3(800.f, 440.f, 0.f), Vector3(800.f, 460.f, 0.f), RGBA::WHITE);
	g_theRenderer->DrawLine(Vector3(790.f, 450.f, 0.f), Vector3(810.f, 450.f, 0.f), RGBA::WHITE);
	g_theRenderer->BlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}