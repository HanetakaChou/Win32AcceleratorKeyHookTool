#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <ShellAPI.h>

#include <string.h>
#include <assert.h>

static LRESULT CALLBACK _Internal_LowLevelKeyboardProc(int nCode, ::WPARAM wParam, ::LPARAM lParam);

static LRESULT CALLBACK _Internal_WindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int nCmdShow)
{
	{
		ATOM hAtom;
		WNDCLASSEXW wc;
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.style = 0U;
		wc.lpfnWndProc = &_Internal_WindProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = sizeof(void *);
		wc.hInstance = hInstance;
		wc.hIcon = ::LoadIconW(NULL, IDI_SHIELD);
		wc.hCursor = ::LoadCursorW(NULL, IDC_ARROW);
		wc.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = { L"Win32HotKeyHookTool-Class:0XFFFFFFFF" };
		wc.hIconSm = NULL;
		hAtom = ::RegisterClassExW(&wc);
		assert(hAtom != 0);

		BOOL bRet;

		HWND hDesktop = ::GetDesktopWindow();
		HMONITOR hMonitor = ::MonitorFromWindow(hDesktop, MONITOR_DEFAULTTONEAREST);
		MONITORINFOEXW MonitorInfo;
		MonitorInfo.cbSize = sizeof(MONITORINFOEXW);
		bRet = ::GetMonitorInfoW(hMonitor, &MonitorInfo);
		assert(bRet != 0);

		RECT rect;
		rect.left = (MonitorInfo.rcWork.left + MonitorInfo.rcWork.right) / 2 - 160;
		rect.right = (MonitorInfo.rcWork.left + MonitorInfo.rcWork.right) / 2 + 160;
		rect.top = (MonitorInfo.rcWork.top + MonitorInfo.rcWork.bottom) / 2 - 80;
		rect.bottom = (MonitorInfo.rcWork.top + MonitorInfo.rcWork.bottom) / 2 + 80;
		bRet = ::AdjustWindowRectEx(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, FALSE, WS_EX_APPWINDOW);
		assert(bRet != 0);

		HWND hWnd = ::CreateWindowExW(WS_EX_APPWINDOW, MAKEINTATOM(hAtom), L"Windows桌面系统热键拦截", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hDesktop, NULL, hInstance, NULL);
		assert(hWnd != NULL);
	}

	BOOL bRet;
	MSG msg;
	while ((bRet = ::GetMessageW(&msg, NULL, 0, 0)) != 0)
	{
		assert(bRet != -1);

		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
	}

	assert(msg.message == WM_QUIT);
	return static_cast<int>(msg.wParam);
}

static HWND _Internal_ButtonAltF4 = NULL;
static HWND _Internal_ButtonAltTab = NULL;
static HWND _Internal_ButtonLeftWin = NULL;
static HHOOK _Internal_hHook = NULL;

static LRESULT CALLBACK _Internal_LowLevelKeyboardProc(int nCode, ::WPARAM wParam, ::LPARAM lParam)
{
	if (nCode >= 0)
	{
		::KBDLLHOOKSTRUCT *pKeyboardLowLevel = reinterpret_cast<::KBDLLHOOKSTRUCT *>(lParam);
		switch (pKeyboardLowLevel->vkCode)
		{
		case VK_F4:
		{
			if (
				!(pKeyboardLowLevel->flags & LLKHF_EXTENDED)//Not Extended Key
				&& (pKeyboardLowLevel->flags & LLKHF_ALTDOWN)//ALT Key Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)//Being Pressed
				)
			{
				if (::SendMessageW(_Internal_ButtonAltF4, BM_GETCHECK, 0U, 0U) == BST_CHECKED)
					return 1;//Hook Alt+F4
			}
		}
		break;
		case VK_TAB:
		{
			if (
				!(pKeyboardLowLevel->flags & LLKHF_EXTENDED)//Not Extended Key
				&& (pKeyboardLowLevel->flags & LLKHF_ALTDOWN)//ALT Key Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)//Being Pressed
				)
			{
				if (::SendMessageW(_Internal_ButtonAltTab, BM_GETCHECK, 0U, 0U) == BST_CHECKED)
					return 1;//Hook Alt+Tab
			}
		}
		break;
		case VK_LWIN:
		{
			if (
				(pKeyboardLowLevel->flags & LLKHF_EXTENDED)//Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN)//ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)//Being Pressed
				)
			{
				if (::SendMessageW(_Internal_ButtonLeftWin, BM_GETCHECK, 0U, 0U) == BST_CHECKED)
					return 1;//Hook Left Win
			}
		}
		break;
		}
	}
	return ::CallNextHookEx(NULL, nCode, wParam, lParam);

}

static LRESULT CALLBACK _Internal_WindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		_Internal_ButtonAltF4 = ::CreateWindowExW(0U, L"Button", L"屏蔽Alt+F4", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 25, 20, 250, 20, hWnd, NULL, NULL, NULL);
		assert(_Internal_ButtonAltF4 != NULL);
		_Internal_ButtonAltTab = ::CreateWindowExW(0U, L"Button", L"屏蔽Alt+Tab", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 25, 50, 250, 20, hWnd, NULL, NULL, NULL);
		assert(_Internal_ButtonAltTab != NULL);
		_Internal_ButtonLeftWin = ::CreateWindowExW(0U, L"Button", L"屏蔽左Win", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 25, 80, 250, 20, hWnd, NULL, NULL, NULL);
		assert(_Internal_ButtonLeftWin != NULL);
		_Internal_hHook = ::SetWindowsHookExW(WH_KEYBOARD_LL, &_Internal_LowLevelKeyboardProc, NULL, 0U);
		assert(_Internal_hHook != NULL);
		return 0;
	}
	case WM_CLOSE:
	{
		::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);

		//最小化到系统栏
		NOTIFYICONDATAW nid;
		nid.cbSize = sizeof(NOTIFYICONDATAW);
		nid.hWnd = hWnd;
		nid.uID = 7U;
		nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO | NIF_SHOWTIP;
		nid.uCallbackMessage = (WM_APP + 7U);
		nid.hIcon = reinterpret_cast<HICON>(::GetClassLongPtrW(hWnd, GCLP_HICONSM));
		::wcscpy_s(nid.szTip, 64U, L"Windows桌面系统热键拦截");
		::wcscpy_s(nid.szInfo, 200U, L"左键双击还原\r\n右键双击退出\r\n作者：张羽乔");
		nid.uVersion = NOTIFYICON_VERSION_4;
		::wcscpy_s(nid.szInfoTitle, 48U, L"Windows桌面系统热键拦截仍在运行中");
		nid.dwInfoFlags = NIIF_NONE;
		BOOL bRet = ::Shell_NotifyIconW(NIM_ADD, &nid);
		assert(bRet != 0);

		return 0;
	}
	case WM_DESTROY:
	{
		BOOL bRet = ::UnhookWindowsHookEx(_Internal_hHook);
		assert(bRet != 0);

		::PostQuitMessage(0U);
		return 0;
	}
	default:
	{
		return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);

	}
	//系统栏
	case (WM_APP + 7U):
	{
		switch (LOWORD(lParam))//系统栏消息
		{
		case WM_LBUTTONDBLCLK://接收系统栏消息的窗口可以没有CS_DBLCLKS
		{
			NOTIFYICONDATAW nid;
			nid.cbSize = sizeof(NOTIFYICONDATAW);
			nid.hWnd = hWnd;
			nid.uID = 7U;
			BOOL bRet = ::Shell_NotifyIconW(NIM_DELETE, &nid);
			assert(bRet != 0);

			//还原
			::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			return 0;
		}
		case WM_RBUTTONDBLCLK://接收系统栏消息的窗口可以没有CS_DBLCLKS
		{
			BOOL bRet;

			NOTIFYICONDATAW nid;
			nid.cbSize = sizeof(NOTIFYICONDATAW);
			nid.hWnd = hWnd;
			nid.uID = 7U;
			bRet = ::Shell_NotifyIconW(NIM_DELETE, &nid);
			assert(bRet != 0);

			//退出
			bRet = ::DestroyWindow(hWnd);
			assert(bRet != 0);
			return 0;
		}
		default:
			return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}
	}
	}
}