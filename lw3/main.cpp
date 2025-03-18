#include <iostream>
#include "framework.h"
#include "../libgl/libgl.h"
#include "TetrisView.h"
#include "TetrisController.h"

HINSTANCE hInst;                                               // current instance
const TCHAR WINDOW_CLASS_NAME[] = TEXT("gl");                  // window class name
const TCHAR WINDOW_TITLE[] = TEXT("Rotation");     // The title bar text
const UINT_PTR TIMER_ID = 0;

TetrisModel gameModel;
TetrisController gameController(gameModel);
TetrisView gameView;

ATOM MyRegisterClass(HINSTANCE hInstance);

BOOL InitInstance(HINSTANCE, int);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nShowCmd))
	{
		return FALSE;
	}

	while (
		GetMessage(&msg, NULL,
			0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.
		wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WINDOW_CLASS_NAME;
	wcex.hIconSm = nullptr;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(
		WINDOW_CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

float angleX = 0;
float angleY = 0;
float angleZ = 0;

ULONGLONG lastTick = GetTickCount64();

void DrawScene(HWND hWnd)
{
	ClearBuffers(0.1f, 0.1f, 0.1f, 1.0f);

	// Настройка проекции для игрового поля
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 10, 20, 0, -1, 1);

	// Рендеринг игры
	gameView.render(gameModel, GetDC(hWnd));

	EndDrawing();
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);

	DrawScene(hWnd);

	EndPaint(hWnd, &ps);
}

bool OnCreate(HWND hWnd)
{
	SetTimer(hWnd, TIMER_ID, USER_TIMER_MINIMUM, nullptr);
	return InitOpenGL(hWnd);
}

void OnSize(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc
	);
	glViewport(0, 0, rc.right - rc.left, rc.bottom - rc.top);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		if (OnCreate(hWnd))
		{
			return 0;
		}
		else
		{
			return -1;
		}
		break;
	case WM_ERASEBKGND:
		return 1; // делаем вид, что очистили фон окна
		break;
	case WM_SIZE:
		OnSize(hWnd);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, nullptr,
			false);
		break;
	case WM_DESTROY:

		DestroyOpenGL();

		PostQuitMessage(0);
		break;
	default:
		return
			DefWindowProc(hWnd, message, wParam, lParam
			);
	}
	return 0;
}