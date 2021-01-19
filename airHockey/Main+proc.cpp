#include "pch.h"
#include "main.h"

LRESULT Main::MainProc(HWND a, UINT b, WPARAM c, LPARAM d) {

	switch (b) {

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_MOUSEMOVE:
		g_mPosit.x = LOWORD(d);
		g_mPosit.y = HIWORD(d);
		break;

	case WM_TIMER:
		InvalidateRect(a, NULL, false);
		Update();
		break;

	case WM_PAINT:
		PAINTSTRUCT pt;
		HDC hdc = BeginPaint(a, &pt);

		Render(hdc);

		EndPaint(a, &pt);
		break;
	}

	return (DefWindowProc(a, b, c, d));
}