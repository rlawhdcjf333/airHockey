#include "pch.h"
#include "main.h"

HINSTANCE g_hInstance;
HWND g_hWnd;

wstring g_className = L"something";

POINT g_mPosit;

Main *g_main=NULL;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow) {

	g_hInstance = hInstance;

	WNDCLASS wndClass = {};

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = g_className.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindowW(
	g_className.c_str(),
	g_className.c_str(),
	WS_OVERLAPPEDWINDOW,
	WINSTARTX,
	WINSTARTY,
	WINSIZEX,
	WINSIZEY,
	NULL,
	(HMENU)NULL,
	hInstance,
	NULL);

	RECT windowRect = {};
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = WINSIZEX;
	windowRect.bottom = WINSIZEY;

	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(g_hWnd, NULL, WINSTARTX, WINSTARTY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(g_hWnd, cmdShow);

	MSG message;

	g_main = new Main;
	g_main->Init();

	while (GetMessageW(&message,0, 0, 0)) {

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	g_main->Release();
	delete g_main;

	return message.wParam;
	}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	if (g_main != NULL) {

		return g_main->MainProc(hWnd, iMessage, wParam, lParam);
	}

	return (DefWindowProcW(hWnd, iMessage, wParam, lParam));
}