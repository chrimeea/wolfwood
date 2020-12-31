#include <windows.h>
#include "rendering\CRenderer.h"
#include "rendering\CMD2Model.h"
#include "utils\Logger.h"
#include "rendering\vector.h"
#include "game\AnimatedEntity.h"
#include "game\Scene.h"
#include "utils\Dictionary.h"
#include "utils\Config.h"
#include "rendering\CMeshBufferPool.h"
#include "background\Background.h"
#include "game\events\Source.h"
#include "game\events\EventsManager.h"
#include "game\events\KeyPressedEvent.h"

#include "game\scripting\Console.h"

HDC			hDC=NULL;
HGLRC		hRC=NULL;
HWND		hWnd=NULL;
HINSTANCE	hInstance;

bool	keys[256];
bool	active=TRUE;
bool	fullscreen=TRUE;

CRenderer*		g_renderer;
float			start_time,ctime;
LARGE_INTEGER	ticks_freq;

int posx = 600, posy = 400;
const int pos_offset = 50;

Console *c;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void InitTime()
{
	LARGE_INTEGER ticks;
	QueryPerformanceFrequency(&ticks_freq);
	QueryPerformanceCounter(&ticks);
	start_time=(float)ticks.QuadPart/(float)ticks_freq.QuadPart;
}

int InitApp()
{

	Config::Init();
	Logger::Init();
	Dictionary::Init();

	InitTime();

    g_renderer = CRenderer::GetInstance();
	CMeshBufferPool::getInstance();
	Background::GetInstance();

    g_renderer->InitializeGL();

//	Scene::GetInstance()->AddEntity(new AnimatedEntity(0, 50, 0));
//	Scene::GetInstance()->AddEntity(new AnimatedEntity(0, 50, 50));
	Scene::GetInstance()->AddEntity(new AnimatedEntity(0, 0, 50));

	Background::GetInstance()->LoadBackground(0);

	c = new Console();
	c->Activate();

	Config::Close();

    return TRUE;
}

void ReSizeScene(int width, int height)
{
    g_renderer->ResizeScene(width,height);
}

void UpdateScene()
{
	// First Update Time
	LARGE_INTEGER ticks;
	QueryPerformanceCounter(&ticks);
	ctime=(float)ticks.QuadPart/(float)ticks_freq.QuadPart - start_time;

	// Update Character : position, frame etc.
	Scene::GetInstance()->NextFrame(ctime);

}

int DrawScene()
{
    g_renderer->BeginScene();
		Background::GetInstance()->Render(posx, posy);
		Scene::GetInstance()->RenderAll();
	g_renderer->EndScene();

	c->Render();

    return TRUE;
}

void CloseApp()
{
	CRenderer::Close();
	CMeshBufferPool::Close();
	Dictionary::Close();
	Logger::Close();

	delete c;
}

void KillWindow()
{

	CloseApp();

	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL,NULL))
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC))
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;
	}

	if (!UnregisterClass("Wolfwood",hInstance))
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;
	}
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag,int freq)
{
	int     	PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;

	fullscreen=fullscreenflag;

	hInstance			= GetModuleHandle(NULL);
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "Wolfwood";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= width;
		dmScreenSettings.dmPelsHeight	= height;
		dmScreenSettings.dmBitsPerPel	= bits;
        dmScreenSettings.dmDisplayFrequency = freq;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;
		
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)
	{
		dwExStyle=WS_EX_APPWINDOW;
		dwStyle=WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	if (!(hWnd=CreateWindowEx(	dwExStyle,
								"Wolfwood",
								title,
								dwStyle |
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								0, 0,
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,
								NULL,
								hInstance,
								NULL)))
	{
		KillWindow();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	if (!(hDC=GetDC(hWnd)))
	{
		KillWindow();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		KillWindow();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		KillWindow();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hRC=wglCreateContext(hDC)))
	{
		KillWindow();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!wglMakeCurrent(hDC,hRC))
	{
		KillWindow();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeScene(width, height);

	if (!InitApp())
	{
		KillWindow();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(	HWND	hWnd,
							UINT	uMsg,
							WPARAM	wParam,
							LPARAM	lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE:
		{
			if (!HIWORD(wParam))
			{
				active=TRUE;
			}
			else
			{
				active=FALSE;
			}

			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			return 0;
		}

		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			EventsManager::GetInstance()->TriggerEvent(
				new KeyPressedEvent(
				new Source(SOURCE_TYPE_KEYBOARD), MapVirtualKey(wParam, 2)));
			return 0;
		}
		case WM_SIZE:
		{
			ReSizeScene(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}

	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	MSG		msg;
	BOOL	done=FALSE;

	if (!CreateGLWindow("Wolfwood",1024,768,32,fullscreen,100))
	{
		return 0;
	}

	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done=TRUE;
				}
				else
				{
					UpdateScene();
					DrawScene();
					SwapBuffers(hDC);
				}
				if (keys[VK_F1])
				{
					keys[VK_F1]=FALSE;
					KillWindow();
					fullscreen=!fullscreen;
					if (!CreateGLWindow("Wolfwood",1024,768,32,fullscreen,100))
					{
						return 0;
					}
				}
				if(keys[VK_UP])
				{
					keys[VK_UP] = FALSE;
					if((posy - pos_offset) >= 0) posy -= pos_offset;
				}
				if(keys[VK_DOWN])
				{
					keys[VK_DOWN] = FALSE;
					if((posy + pos_offset + SCREEN_HEIGHT) <= 
						(Background::GetInstance()->GetHeight() - 1)) posy += pos_offset;
				}
				if(keys[VK_RIGHT])
				{
					keys[VK_RIGHT] = FALSE;
					if((posx + pos_offset + SCREEN_WIDTH) <= 
						(Background::GetInstance()->GetWidth() - 1)) posx += pos_offset;
				}
				if(keys[VK_LEFT])
				{
					keys[VK_LEFT] = FALSE;
					if((posx - pos_offset) >= 0) posx -= pos_offset;
				}
			}

		}	
	}

	KillWindow();
	return (msg.wParam);
}