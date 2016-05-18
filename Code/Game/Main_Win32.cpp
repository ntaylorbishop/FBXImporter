#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <gl/gl.h>
#include <math.h>
#include <cassert>
#include <crtdbg.h>
#pragma comment( lib, "opengl32" ) // Link in the OpenGL32.lib static library

#include "Engine/General/Core/GameEngine.hpp"
#include "Game/TheUI.hpp"
#include "Game/TheApp.hpp"
#include "Game/TheGame.hpp"
#include "Engine/General/Time/Time.hpp"
#include "Engine/Renderer/Framebuffer.hpp"
#include "Engine/Renderer/General/Texture.hpp"

#define UNUSED(x) (void)(x);

//--------------Window Creation----------------------------
const int OFFSET_FROM_WINDOWS_DESKTOP = 10;
const int WINDOW_PHYSICAL_WIDTH = 1600;
const int WINDOW_PHYSICAL_HEIGHT = 900;
const double VIEW_LEFT = 0.0;
const double VIEW_RIGHT = 1600.0;
const double VIEW_BOTTOM = 0.0;
const double VIEW_TOP = VIEW_RIGHT * static_cast<double>(WINDOW_PHYSICAL_HEIGHT) / static_cast<double>(WINDOW_PHYSICAL_WIDTH);

HWND g_hWnd = nullptr;
HDC g_displayDeviceContext = nullptr;
HGLRC g_openGLRenderingContext = nullptr;
const char* APP_NAME = "Graphics Suite";

//TODO: THIS IS JANKY AF
Framebuffer* m_fbo;

LRESULT CALLBACK WindowsMessageHandlingProcedure(HWND windowHandle, UINT wmMessageCode, WPARAM wParam, LPARAM lParam) {
	unsigned char asKey = (unsigned char)wParam;
	switch (wmMessageCode) {
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		g_theInputSystem->Quitting(true);
		return 0;
	case WM_KEYDOWN:
		g_theInputSystem->SetKeyDownStatus(asKey, true);
		g_theApparatusEngine->ProcessInput(asKey, true);

		if (asKey == VK_ESCAPE) {
			if (!g_theApparatusEngine->IsConsoleOpen()) {
				g_theInputSystem->Quitting(true);
				return 0;
			}
		}
		break;
	case WM_CHAR:
		g_theApparatusEngine->SendInputToConsole(asKey);
		break;

	case WM_KEYUP:
		g_theInputSystem->SetKeyDownStatus(asKey, false);
		g_theApparatusEngine->ProcessInput(asKey, false);

		break;
	case WM_SETFOCUS:
		g_theApp->OnGainedFocus();
		break;
	case WM_KILLFOCUS:
		g_theApp->OnLostFocus();
		break;
	case WM_LBUTTONDOWN:
		g_theInputSystem->SetMouseBtnDown(MOUSE_LEFT, true);
		break;
	case WM_LBUTTONUP:
		g_theInputSystem->SetMouseBtnDown(MOUSE_LEFT, false);
		break;
	case WM_MBUTTONDOWN:
		g_theInputSystem->SetMouseBtnDown(MOUSE_MIDDLE, true);
		break;
	case WM_MBUTTONUP:
		g_theInputSystem->SetMouseBtnDown(MOUSE_MIDDLE, false);
		break;
	case WM_RBUTTONDOWN:
		g_theInputSystem->SetMouseBtnDown(MOUSE_RIGHT, true);
		break;
	case WM_RBUTTONUP:
		g_theInputSystem->SetMouseBtnDown(MOUSE_RIGHT, false);
		break;
	case WM_MOUSEWHEEL:
		g_theInputSystem->SetMouseWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam));
		g_theApparatusEngine->SetMouseWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	}

	return DefWindowProc(windowHandle, wmMessageCode, wParam, lParam);
}

void CreateOpenGLWindow(HINSTANCE applicationInstanceHandle) {
	// Define a window class
	WNDCLASSEX windowClassDescription;
	memset(&windowClassDescription, 0, sizeof(windowClassDescription));
	windowClassDescription.cbSize = sizeof(windowClassDescription);
	windowClassDescription.style = CS_OWNDC; // Redraw on move, request own Display Context
	windowClassDescription.lpfnWndProc = static_cast<WNDPROC>(WindowsMessageHandlingProcedure); // Assign a win32 message-handling function
	windowClassDescription.hInstance = GetModuleHandle(NULL);
	windowClassDescription.hIcon = NULL;
	windowClassDescription.hCursor = NULL;
	windowClassDescription.lpszClassName = TEXT("Simple Window Class");
	RegisterClassEx(&windowClassDescription);

	// 	const DWORD windowStyleFlags = WS_POPUP;
	// 	const DWORD windowStyleExFlags = WS_EX_APPWINDOW | WS_EX_TOPMOST;

	const DWORD windowStyleFlags = WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_SYSMENU | WS_OVERLAPPED;
	const DWORD windowStyleExFlags = WS_EX_APPWINDOW;

	RECT desktopRect;
	HWND desktopWindowHandle = GetDesktopWindow();
	GetClientRect(desktopWindowHandle, &desktopRect);

	RECT windowRect = { OFFSET_FROM_WINDOWS_DESKTOP, OFFSET_FROM_WINDOWS_DESKTOP, OFFSET_FROM_WINDOWS_DESKTOP + WINDOW_PHYSICAL_WIDTH, OFFSET_FROM_WINDOWS_DESKTOP + WINDOW_PHYSICAL_HEIGHT };
	AdjustWindowRectEx(&windowRect, windowStyleFlags, FALSE, windowStyleExFlags);

	WCHAR windowTitle[1024];
	MultiByteToWideChar(GetACP(), 0, APP_NAME, -1, windowTitle, sizeof(windowTitle) / sizeof(windowTitle[0]));
	g_hWnd = CreateWindowEx(
		windowStyleExFlags,
		windowClassDescription.lpszClassName,
		windowTitle,
		windowStyleFlags,
		windowRect.left,
		windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		applicationInstanceHandle,
		NULL
		);

	ShowWindow(g_hWnd, SW_SHOW);
	SetForegroundWindow(g_hWnd);
	SetFocus(g_hWnd);

	g_displayDeviceContext = GetDC(g_hWnd);

	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(cursor);

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	memset(&pixelFormatDescriptor, 0, sizeof(pixelFormatDescriptor));
	pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 24;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cAccumBits = 0;
	pixelFormatDescriptor.cStencilBits = 8;

	int pixelFormatCode = ChoosePixelFormat(g_displayDeviceContext, &pixelFormatDescriptor);
	SetPixelFormat(g_displayDeviceContext, pixelFormatCode, &pixelFormatDescriptor);
	g_openGLRenderingContext = wglCreateContext(g_displayDeviceContext);
	wglMakeCurrent(g_displayDeviceContext, g_openGLRenderingContext);

	//Set some standard 2D settings up. TheGame will change it if it wants
	g_theRenderer->EnableBlending();
	g_theRenderer->BlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	g_theRenderer->LineWidth(2.f);
	g_theRenderer->EnableLineSmoothing();
	g_theRenderer->EnableGLAlphaFunc(0.1f);
}

//---------------------------------------------------------------------------------------------------------------------------
//FBO STUFF
//---------------------------------------------------------------------------------------------------------------------------
Mesh* m_fboMesh;
Material* m_fboMaterial;
MeshRenderer* m_meshRenderer;
float m_age;

void ChangeFBO(int whichFBO) {
	if (whichFBO == 1) {
		m_fboMaterial = g_theMaterialManager->GetMaterial("fbo1");
	}
	else if (whichFBO == 2) {
		m_fboMaterial = g_theMaterialManager->GetMaterial("fbo2");
	}
	else if (whichFBO == 3) {
		m_fboMaterial = g_theMaterialManager->GetMaterial("fbo3");
	}
	else if (whichFBO == 4) {
		m_fboMaterial = g_theMaterialManager->GetMaterial("fbo4");
	}
	else if (whichFBO == 5) {
		m_fboMaterial = g_theMaterialManager->GetMaterial("fbo5");
	}
	else if (whichFBO == 6) {
		m_fboMaterial = g_theMaterialManager->GetMaterial("fbo6");
	}
}

void RenderInitialization() {
	g_theMaterialManager = new MaterialManager();

	m_meshRenderer = new MeshRenderer();
	m_fboMesh = new Mesh(VertexDefinition::TEXTUREDVERTEX);
	m_fboMaterial = g_theMaterialManager->GetMaterial("fbo1");
	
	//Create verts
	std::vector<TexturedVertex> m_vertsForMesh;

	m_vertsForMesh.push_back(TexturedVertex(Vector3(-1.f, 1.f, 0.f), RGBA::WHITE, Vector2(0.f, 0.f))); //TL
	m_vertsForMesh.push_back(TexturedVertex(Vector3(-1.f, -1.f, 0.f), RGBA::WHITE, Vector2(0.f, 1.f))); //BL
	m_vertsForMesh.push_back(TexturedVertex(Vector3(1.f, -1.f, 0.f), RGBA::WHITE, Vector2(1.f, 1.f))); //BR
	m_vertsForMesh.push_back(TexturedVertex(Vector3(1.f, 1.f,  0.f), RGBA::WHITE, Vector2(1.f, 0.f))); //TR

	std::vector<uint16_t> meshIndices = {
		0, 1, 2,
		0, 2, 3
	};

	m_age = 0.f;

	m_fboMesh->UpdateMesh(m_vertsForMesh, meshIndices);
}
void RenderPostProcess(Mesh* mesh, Material* mat) {

	Matrix4 view = Matrix4::IDENTITY;
	Matrix4 proj = Matrix4::IDENTITY;
	Matrix4 model = Matrix4::IDENTITY;

	g_theRenderer->DisableBackfaceCulling();

	m_meshRenderer->RenderMeshWithMaterial(*mesh, mat);

	//mesh->DrawMeshWithMaterialFBO(mat, m_fbo);
}
//---------------------------------------------------------------------------------------------------------------------------
//END FBO
//---------------------------------------------------------------------------------------------------------------------------



//-----------Main game Loop--------------------------------
void RunMessagePump() {
	MSG queuedMessage;
	for (;;)
	{
		const BOOL wasMessagePresent = PeekMessage(&queuedMessage, NULL, 0, 0, PM_REMOVE);
		if (!wasMessagePresent)
		{
			break;
		}

		TranslateMessage(&queuedMessage);
		DispatchMessage(&queuedMessage);
	}
}

bool m_continuouslyUpdating = true;

void Update() {

	if (g_theInputSystem->GetKeyDown(VK_F2))
		m_continuouslyUpdating = !m_continuouslyUpdating;

	if (m_continuouslyUpdating || g_theInputSystem->GetKeyDown(VK_F3)) {

		static double s_timeLastFrameBegan = GetCurrentTimeSeconds();

		double timeThisFrameBegan = GetCurrentTimeSeconds();
		float deltaSeconds = static_cast<float>(timeThisFrameBegan - s_timeLastFrameBegan); //In seconds

		s_timeLastFrameBegan = timeThisFrameBegan;

		g_theApparatusEngine->Update(deltaSeconds);
		g_theGame->Update(deltaSeconds);
		g_theUI->Update(deltaSeconds);

		//SWITCH FBO
		if (g_theInputSystem->GetKeyDown('1')) {
			ChangeFBO(1);
		}
		else if (g_theInputSystem->GetKeyDown('2')) {
			ChangeFBO(2);
		}
		else if (g_theInputSystem->GetKeyDown('3')) {
			ChangeFBO(3);
		}
		else if (g_theInputSystem->GetKeyDown('4')) {
			ChangeFBO(4);
		}
		else if (g_theInputSystem->GetKeyDown('5')) {
			ChangeFBO(5);
		}


		m_age += deltaSeconds;

		Material* fbo1 = g_theMaterialManager->GetMaterial("fbo1");
		Material* fbo2 = g_theMaterialManager->GetMaterial("fbo2");
		Material* fbo3 = g_theMaterialManager->GetMaterial("fbo3");
		Material* fbo4 = g_theMaterialManager->GetMaterial("fbo4");
		Material* fbo5 = g_theMaterialManager->GetMaterial("fbo5");
		Material* fbo6 = g_theMaterialManager->GetMaterial("fbo6");

		Uniform_FLOAT* age1 = static_cast<Uniform_FLOAT*>(fbo1->GetUniform("gAge"));
		Uniform_FLOAT* age2 = static_cast<Uniform_FLOAT*>(fbo2->GetUniform("gAge"));
		Uniform_FLOAT* age3 = static_cast<Uniform_FLOAT*>(fbo3->GetUniform("gAge"));
		Uniform_FLOAT* age4 = static_cast<Uniform_FLOAT*>(fbo4->GetUniform("gAge"));
		Uniform_FLOAT* age5 = static_cast<Uniform_FLOAT*>(fbo5->GetUniform("gAge"));
		Uniform_FLOAT* age6 = static_cast<Uniform_FLOAT*>(fbo6->GetUniform("gAge"));

		age1->SetData(m_age);
		age2->SetData(m_age);
		age3->SetData(m_age);
		age4->SetData(m_age);
		age5->SetData(m_age);
		age6->SetData(m_age);

		g_theMaterialManager->UpdateUniformOnMaterial("fbo1", age1);
		g_theMaterialManager->UpdateUniformOnMaterial("fbo2", age2);
		g_theMaterialManager->UpdateUniformOnMaterial("fbo3", age3);
		g_theMaterialManager->UpdateUniformOnMaterial("fbo4", age4);
		g_theMaterialManager->UpdateUniformOnMaterial("fbo5", age5);
		g_theMaterialManager->UpdateUniformOnMaterial("fbo6", age6);
	}

}
void Render() {
	//FBO CRAP
	g_theRenderer->ClearScreen(0.f, 1.f, 0.f);


	g_theRenderer->FramebufferBind(m_fbo);
	g_theRenderer->ClearScreen(0.1f, 0.1f, 0.1f);

	g_theGame->Render();
	g_theApparatusEngine->RenderDebugRenderer();

	g_theRenderer->FramebufferBind(NULL);
	
	RenderPostProcess(m_fboMesh, m_fboMaterial);
	//g_theRenderer->FramebufferCopyToBack(m_fbo);

	g_theUI->Render();
	g_theApparatusEngine->RenderConsole();

	SwapBuffers(g_displayDeviceContext);
}
void RunFrame() {
	RunMessagePump();
	Update();
	Render();
}

//-----------Initialization and shutdown-------------------
void InitializeEngine() {
	g_theApparatusEngine = new GameEngine();
	g_theApparatusEngine->Initialize();
}
void InitializeGame(HINSTANCE applicationInstanceHandle) {
	g_theApp = new TheApp(ScreenCoords(1600, 900));

	SetProcessDPIAware();
	CreateOpenGLWindow(applicationInstanceHandle);

	InitializeEngine();
	RenderInitialization();

	g_theUI = new TheUI();
	g_theGame = new TheGame();

	//---------------------------------------------------------------------------------------------------------------------------
	//FBO STUFF
	//---------------------------------------------------------------------------------------------------------------------------
	std::vector<Texture*> diffuseTexturesForFBO;
	Uniform_SAMPLER2D* samplerUniform = static_cast<Uniform_SAMPLER2D*>(m_fboMaterial->GetUniform("SAMPLER2D"));
	Sampler2D sampler = samplerUniform->GetData();
	Texture* diffuse = sampler.GetTextureByName("gTexDiffuse");
	Texture* depthStencil = sampler.GetTextureByName("gTexDepth");
	
	diffuseTexturesForFBO.push_back(diffuse);

	m_fbo = new Framebuffer(diffuseTexturesForFBO, 1, depthStencil);
}
void Shutdown() {
	delete g_theGame;
	g_theGame = nullptr;
	delete g_theApparatusEngine;
	g_theApparatusEngine = nullptr;
	delete g_theApp;
	g_theApp = nullptr;
	delete g_theMaterialManager;
	g_theMaterialManager = nullptr;
}

//Driver
int WINAPI WinMain(HINSTANCE applicationInstanceHandle, HINSTANCE, LPSTR commandLineString, int) {
	UNUSED(commandLineString);
	InitializeGame(applicationInstanceHandle);

	while (!g_theInputSystem->HasQuit())
		RunFrame();

	Shutdown();
	return 0;
}