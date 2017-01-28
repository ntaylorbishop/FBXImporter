
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Engine/Renderer/Renderer/TheRenderer.hpp"

class DummyWin32OGLContext
{
	HWND    mHWND;
	HGLRC   mHGLRC;

public:
	PFNWGLCHOOSEPIXELFORMATARBPROC      mpWglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC   mpWglCreateContextAttribsARB;

public:
	DummyWin32OGLContext() :
		mHWND(NULL),
		mHGLRC(NULL),
		mpWglChoosePixelFormatARB(NULL),
		mpWglCreateContextAttribsARB(NULL)
	{
		static bool isClassReg;
		if (!isClassReg)
		{
			WNDCLASSEX wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = (WNDPROC)wndProc_s;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = GetModuleHandle(NULL);
			wcex.hIcon = NULL;
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = NULL;
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = "DWINDOWS_TEMP_CLASS";
			wcex.hIconSm = NULL;
			RegisterClassEx(&wcex);
		}
	}

	~DummyWin32OGLContext()
	{
		Close();
	}

	void Open()
	{
		mHWND = CreateWindowEx(
			0,
			"DWINDOWS_TEMP_CLASS",
			"Temp",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			(HMENU)NULL,
			GetModuleHandle(NULL),
			(LPVOID)this);

		ASSERT_OR_DIE(mHWND != NULL);

		mpWglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
		mpWglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	}

	void Close()
	{
		if (mHWND)
		{
			DestroyWindow(mHWND);
			mHWND = NULL;
		}

		if (mHGLRC)
		{
			wglDeleteContext(mHGLRC);
			mHGLRC = NULL;
		}
	}

private:
	void onCreate(HWND hWnd)
	{
		HDC hdc = GetDC(hWnd);

		int nPixelFormat;
		static PIXELFORMATDESCRIPTOR    pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
			1,                              // Version of this structure
			PFD_DRAW_TO_WINDOW |            // Draw to Window (not to bitmap)
			PFD_SUPPORT_OPENGL |            // Support OpenGL calls in window
			PFD_DOUBLEBUFFER |              // Double buffered mode
			PFD_STEREO_DONTCARE,
			PFD_TYPE_RGBA,                  // RGBA Color mode
			32,                             // Want the display bit depth
			0,0,0,0,0,0,                    // Not used to select mode
			0,0,                            // Not used to select mode
			0,0,0,0,0,                      // Not used to select mode
			24,                             // Size of depth buffer
			8,                              // bit stencil
			0,                              // Not used to select mode
			PFD_MAIN_PLANE,                 // Draw in main plane
			0,                              // Not used to select mode
			0,0,0
		};

		nPixelFormat = ChoosePixelFormat(hdc, &pfd);

		BOOL success = SetPixelFormat(hdc, nPixelFormat, &pfd);
		if (!success)
		{
			ERROR_AND_DIE("Could not create dummy opengl context");
			return;
		}

		mHGLRC = wglCreateContext(hdc);

		if (!mHGLRC)
			ERROR_AND_DIE("Failed to create the temp context");

		wglMakeCurrent(hdc, mHGLRC);
	}

	static LRESULT CALLBACK wndProc_s(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_CREATE)
		{
			CREATESTRUCT    *csp = (CREATESTRUCT *)lParam;
			((DummyWin32OGLContext *)csp->lpCreateParams)->onCreate(hWnd);
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
};

//==================================================================
LRESULT WndProc_s(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DWindow *pWin = NULL;

	if (message == WM_CREATE)
	{
		CREATESTRUCT    *csp;

		csp = (CREATESTRUCT *)lParam;
		pWin = (DWindow *)csp->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWin);

		DummyWin32OGLContext    dummyCtx;

		dummyCtx.Open();

		HDC hdc = GetDC(hWnd);
		pWin->mWIN32_HDC = hdc;
		pWin->mWIN32_HWnd = hWnd;

		HGLRC   hRootHGLRC = pWin->GetRootHGLRG();

		int chooseAttribs[] = {
			WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
			WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB,         COLOR_BITS,
			WGL_ALPHA_BITS_ARB,         ALPHA_BITS,
			WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
			WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
			WGL_SAMPLE_BUFFERS_ARB,     GL_TRUE,
			WGL_SAMPLES_ARB,            DWindows::mWin32_CurMsampleCnt,
			0,0 };

		int     pixelFormat;
		UINT    numFormats;
		if (FALSE == dummyCtx.mpWglChoosePixelFormatARB(hdc, chooseAttribs, NULL, 1, &pixelFormat, &numFormats))
		{
			DWORD err = GetLastError();
			DEX_RUNTIME_ERROR("Failed to choose the pixel format. Error %u", err);
		}

		static PIXELFORMATDESCRIPTOR    dummyPFD = {
			sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
			1,                              // Version of this structure
			PFD_DRAW_TO_WINDOW |            // Draw to Window (not to bitmap)
			PFD_SUPPORT_OPENGL |            // Support OpenGL calls in window
			PFD_DOUBLEBUFFER |              // Double buffered mode
			PFD_STEREO_DONTCARE |
			0,
			PFD_TYPE_RGBA,                  // RGBA Color mode
			COLOR_BITS,                     // Want the display bit depth
			0,0,0,0,0,0,                    // Not used to select mode
			0,0,                            // Not used to select mode
			0,0,0,0,0,                      // Not used to select mode
			DEPTH_BITS,                     // Size of depth buffer
			STENCIL_BITS,                   // bit stencil
			0,                              // Not used to select mode
			PFD_MAIN_PLANE,                 // Draw in main plane
			0,                              // Not used to select mode
			0,0,0
		};
		if (FALSE == SetPixelFormat(hdc, pixelFormat, &dummyPFD))
		{
			DWORD err = GetLastError();
			DEX_RUNTIME_ERROR("Failed to set the pixel format. Error %u", err);
		}

		int createAttrib[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB,  3,
			WGL_CONTEXT_MINOR_VERSION_ARB,  0,
			0,0 };

		pWin->mWIN32_HGLRC =
			dummyCtx.mpWglCreateContextAttribsARB(hdc, hRootHGLRC, createAttrib);

		if (pWin->mWIN32_HGLRC == NULL)
		{
			DWORD err = GetLastError();
			DEX_RUNTIME_ERROR("Failed to create the OpenGL context. Error %u", err);
		}

		wglMakeCurrent(hdc, pWin->mWIN32_HGLRC);

		dummyCtx.Close();

		static bool isGlewInitialized;
		if NOT(isGlewInitialized)
		{
			if (GLEW_OK != glewInit())
				DEX_RUNTIME_ERROR("Failed to initialize GLEW");

			#if defined(D_GLES20)
			if NOT(glewIsSupported("GL_ARB_shading_language_100"))
				DEX_RUNTIME_ERROR(
					"Shading language not supported."
					" Make sure that the drivers support OpenGL 2.0 or better.");
			#endif
		}

		//wglMakeCurrent( pWin->mWIN32_HDC, pWin->mWIN32_HGLRC );
		wglMakeCurrent(NULL, NULL);
		wglMakeCurrent(hdc, pWin->mWIN32_HGLRC);
	}

	// not necessarily available.. some messages happen before the create !!
	pWin = (DWindow *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (pWin == NULL)
		return DefWindowProc(hWnd, message, wParam, lParam);

	// if we have the app installed..
	if (pWin->mpSuper)
		if (pWin->mpSuper->WndProc(*pWin, hWnd, message, wParam, lParam))
			return TRUE;

	return DefWindowProc(hWnd, message, wParam, lParam);
}