#pragma once

#include <Windows.h>
#include <Winuser.h>
#include <CommCtrl.h>

#define IDC_COMBOBOX 1001
#define IDC_SUBMITBUTTON 1001

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	~Window();

	bool ProcessMessages();
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
};
