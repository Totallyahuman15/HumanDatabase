#include "window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HWND hButton;

	switch (uMsg)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 20, 20, "Hello World!", wcslen(L"Hello World!"));

		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		hButton = CreateWindowEx(
			0,
			"BUTTON",
			"Click Me!",
			WS_VISIBLE | WS_CHILD,
			100,
			100,
			100,
			30,
			hWnd,
			(HMENU)ID_MY_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
		SetWindowLongPtr(hWnd, WS_CHILD, (LONG)hButton);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_MY_BUTTON)
		{
			MessageBox(hWnd, "Harder~", ";3", MB_OK);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
	: m_hInstance(GetModuleHandle(nullptr))
{
	const char szClassName[ ] = "HDWindowClass";

	WNDCLASS wc = {};
	wc.lpszClassName = szClassName;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadIcon(NULL, IDC_NO);
	wc.lpfnWndProc = WindowProc;

	RegisterClass(&wc);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 640;
	int height = 480;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		szClassName,
		"Human Database Client",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
	const char szClassName[] = "HDWindowClass";

	UnregisterClass(szClassName, m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}
