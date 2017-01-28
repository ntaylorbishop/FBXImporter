#pragma once

#include <string>
#include "Engine/General/Console/Console.hpp"
#include "Engine/General/Input/InputSystem.hpp"
#include "Engine/Renderer/Renderer/TheDebugRenderer.hpp"
#include "Engine/General/Utils/TheLogger.hpp"
#include "Engine/General/UI/UISystem.hpp"
#include "Engine/Tools/FBX.hpp"

typedef void(*console_commmand_cb)(Command&);

class GameEngine;
extern GameEngine* g_theApparatusEngine;

class GameEngine {
public:
	//STRUCTORS AND INITIALIZATION
	GameEngine();
	void Initialize();
	void Shutdown();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	void RenderDebugRenderer();
	void RenderConsole();
	void RenderUI() const;

	//CONSOLE API
	void BindKeyToConsole(unsigned char asKey);
	void PrintOutputToConsole(std::string output, eConsoleColor color);

	void SendInputToConsole(unsigned char asKey);
	void RegisterCommandToConsole(std::string name, console_command_cb cb);
	void RunConsoleCommand(std::string commandLine);
	void ClearConsole();

	bool IsConsoleOpen();

	//INPUT
	void ProcessInput(unsigned char asKey, bool isDown);
	bool GetKeyDown(unsigned char asKey);
	bool GetKey(unsigned char asKey);

	void SetMouseWheelDelta(short wheelDelta);
	bool GetMouseWheelUp();
	bool GetMouseWheelDown();

	//WINDOW



	//FOR ENGINE USE ONLY
	unsigned char GetKeyBindForConsole();

private:
	void ToggleConsole();

private:
	Console* m_developerConsole;
	unsigned char m_asKeyForConsole;

	//INPUT
	bool m_isKeyDown[NUM_KEYS];
	int m_mouseWheelUpDelta;
	int m_mouseWheelDownDelta;

};

void FbxListScene(Command& args);