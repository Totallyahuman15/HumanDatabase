#include "window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hComboBox;
	HWND hButton;

	switch (uMsg)
	{
	case WM_CREATE:
		hComboBox = CreateWindowEx(
			0,
			WC_COMBOBOX,
			TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			0, 0,
			200, 200,
			hWnd,
			(HMENU)IDC_COMBOBOX,
			GetModuleHandle(nullptr),
			NULL
		);
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Item 1");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Item 2");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Item 3");

		hButton = CreateWindowEx(
			0,
			"BUTTON",
			"Submit",
			WS_CHILD | WS_VISIBLE,
			0, 20,
			100, 30,
			hWnd,
			(HMENU)IDC_SUBMITBUTTON,
			GetModuleHandle(nullptr),
			NULL
		);

		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			if (LOWORD(wParam) == IDC_SUBMITBUTTON)
			{
				hComboBox = GetDlgItem(hWnd, IDC_SUBMITBUTTON);
				int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
				switch (selectedIndex)
				{
				case 0:
					MessageBox(hWnd, TEXT("Item 1 selected."), TEXT("Selected Item"), MB_OK);
					break;
				case 1:
					MessageBox(hWnd, TEXT("Item 2 selected."), TEXT("Selected Item"), MB_OK);
					break;
				case 2:
					MessageBox(hWnd, TEXT("Item 3 selected."), TEXT("Selected Item"), MB_OK);
					break;
				default:
					MessageBox(hWnd, TEXT("No item selected"), TEXT("Selected Item"), MB_OK);
					break;
				}
			}
		}
	case WM_CLOSE:
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
