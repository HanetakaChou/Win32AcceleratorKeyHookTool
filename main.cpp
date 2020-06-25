
#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <ShellAPI.h>

#include <string.h>
#include <assert.h>

#include "resource.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

static INT_PTR CALLBACK _Internal_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int nCmdShow)
{
	assert(hInstance == HINST_THISCOMPONENT);

	return static_cast<int>(DialogBoxW(hInstance, MAKEINTRESOURCE(IDD_DIALOG), GetDesktopWindow(), _Internal_DlgProc));
}

static bool _Internal_Hook_AltF4 = false;
static bool _Internal_Hook_AltTab = false;
static bool _Internal_Hook_LWin = false;
static bool _Internal_Hook_ESC = false;

static LRESULT CALLBACK _Internal_LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		KBDLLHOOKSTRUCT *pKeyboardLowLevel = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

		switch (pKeyboardLowLevel->vkCode)
		{
		case VK_F4:
		{
			assert(pKeyboardLowLevel->vkCode == VK_F4);

			if (_Internal_Hook_AltF4)
			{
				if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
					&& (pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Pressed
					&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

				{
					return 1; //Hook Alt+F4
				}
			}
		}
		break;

		case VK_TAB:
		{
			assert(pKeyboardLowLevel->vkCode == VK_TAB);

			if (_Internal_Hook_AltTab)
			{
				if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
					&& (pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Pressed
					&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
				{
					return 1; //Hook Alt+Tab
				}
			}
		}
		break;

		case VK_LWIN:
		{
			assert(pKeyboardLowLevel->vkCode == VK_LWIN);

			if (_Internal_Hook_LWin)
			{
				if ((pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Extended Key
					//&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
					&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
				{
					return 1; //Hook L-Win
				}
			}
		}
		break;

		case VK_ESCAPE:
		{
			assert(pKeyboardLowLevel->vkCode == VK_ESCAPE);

			if (_Internal_Hook_ESC)
			{
				if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
					// && !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
					&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
				{
					return 1; //Hook ESC
				}
			}
		}
		break;
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

static HHOOK _Internal_hHook = NULL;

static INT_PTR CALLBACK _Internal_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		assert(uMsg == WM_INITDIALOG);

		SetClassLongPtrW(hWnd, GCLP_HICON, reinterpret_cast<LONG_PTR>(LoadIconW(HINST_THISCOMPONENT, MAKEINTRESOURCEW(IDI_ICON))));

		LRESULT _res1 = SendDlgItemMessageW(hWnd, IDC_ALTF4, BM_SETCHECK, (_Internal_Hook_AltF4 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res1 == 0);
		LRESULT _res2 = SendDlgItemMessageW(hWnd, IDC_ALTTAB, BM_SETCHECK, (_Internal_Hook_AltTab ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res2 == 0);
		LRESULT _res3 = SendDlgItemMessageW(hWnd, IDC_LWIN, BM_SETCHECK, (_Internal_Hook_LWin ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res3 == 0);
		LRESULT _res4 = SendDlgItemMessageW(hWnd, IDC_ESC, BM_SETCHECK, (_Internal_Hook_ESC ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res4 == 0);

		_Internal_hHook = SetWindowsHookExW(WH_KEYBOARD_LL, &_Internal_LowLevelKeyboardProc, NULL, 0U);
		assert(_Internal_hHook != NULL);
	}
	return TRUE;

	case WM_COMMAND:
	{
		assert(uMsg == WM_COMMAND);

		switch (LOWORD(wParam))
		{
		case IDC_ALTF4:
		{
			_Internal_Hook_AltF4 = (SendDlgItemMessageW(hWnd, IDC_ALTF4, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_ALTTAB:
		{
			_Internal_Hook_AltTab = (SendDlgItemMessageW(hWnd, IDC_ALTTAB, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_LWIN:
		{
			_Internal_Hook_LWin = (SendDlgItemMessageW(hWnd, IDC_LWIN, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_ESC:
		{
			_Internal_Hook_ESC = (SendDlgItemMessageW(hWnd, IDC_ESC, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		default:
			return FALSE;
		}
	}

	//最小化到系统栏
	case WM_CLOSE:
	{
		assert(uMsg == WM_CLOSE);

		SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);

		NOTIFYICONDATAW nid;
		nid.cbSize = sizeof(NOTIFYICONDATAW);
		nid.hWnd = hWnd;
		nid.uID = 7U;
		nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO | NIF_SHOWTIP;
		nid.uCallbackMessage = (WM_APP + 13U);
		nid.hIcon = LoadIconW(HINST_THISCOMPONENT, MAKEINTRESOURCEW(IDI_ICON));
		wcsncpy_s(nid.szTip, L"Win32HotKeyHookTool", 64U);
		wcsncpy_s(nid.szInfo, L"Double click left mouse button to restore!\r\nDouble click right mouse button to exit!\r\nAuthor - YuqiaoZhang <yuqiaozhang@aliyun.com>!", 200U);
		nid.uVersion = NOTIFYICON_VERSION_4;
		wcsncpy_s(nid.szInfoTitle, L"\"Win32HotKeyHookTool\" is still running!", 48U);
		nid.dwInfoFlags = NIIF_NONE;
		BOOL _res = Shell_NotifyIconW(NIM_ADD, &nid);
		assert(_res != FALSE);

		return 0;
	}
	SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
	return TRUE;

	//系统栏
	case (WM_APP + 13U):
	{
		assert(uMsg == (WM_APP + 13U));

		switch (LOWORD(lParam))//系统栏消息
		{
		case WM_LBUTTONDBLCLK://接收系统栏消息的窗口可以没有CS_DBLCLKS
		{
			assert(LOWORD(lParam) == WM_LBUTTONDBLCLK);

			NOTIFYICONDATAW nid;
			nid.cbSize = sizeof(NOTIFYICONDATAW);
			nid.hWnd = hWnd;
			nid.uID = 7U;
			BOOL bRet = Shell_NotifyIconW(NIM_DELETE, &nid);
			assert(bRet != 0);

			//还原
			SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case WM_RBUTTONDBLCLK://接收系统栏消息的窗口可以没有CS_DBLCLKS
		{
			assert(LOWORD(lParam) == WM_RBUTTONDBLCLK);

			NOTIFYICONDATAW nid;
			nid.cbSize = sizeof(NOTIFYICONDATAW);
			nid.hWnd = hWnd;
			nid.uID = 7U;
			BOOL _res1 = Shell_NotifyIconW(NIM_DELETE, &nid);
			assert(_res1 != FALSE);

			//退出
			BOOL _res2 = UnhookWindowsHookEx(_Internal_hHook);
			assert(_res2 != FALSE);

			BOOL _res3 = EndDialog(hWnd, 0);
			assert(_res3 != FALSE);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		default:
			return FALSE;
		}
	}

	default:
		return FALSE;
	}
}

