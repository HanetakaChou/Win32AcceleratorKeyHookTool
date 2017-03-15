#include <winsdkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <atlbase.h>
#include <atlwin.h>

class CWindowImplWin32Hook : public ATL::CWindowImpl<CWindowImplWin32Hook>
{
	::HWND m_ButtonAltF4 = NULL;
	::HWND m_ButtonAltTab = NULL;
	::HWND m_ButtonLeftWin = NULL;
	::HHOOK m_hWin32Hook = NULL;

	//Win32Hook
	static CWindowImplWin32Hook * HookInstance;
	static ::LRESULT CALLBACK LowLevelKeyboardProc(int nCode, ::WPARAM wParam, ::LPARAM lParam)
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
					if (::SendMessageW(HookInstance->m_ButtonAltF4, BM_GETCHECK, 0U, 0U) == BST_CHECKED)
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
					if (::SendMessageW(HookInstance->m_ButtonAltTab, BM_GETCHECK, 0U, 0U) == BST_CHECKED)
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
					if (::SendMessageW(HookInstance->m_ButtonLeftWin, BM_GETCHECK, 0U, 0U) == BST_CHECKED)
						return 1;//Hook Left Win
				}
			}
			break;
			}
		}
		return ::CallNextHookEx(NULL, nCode, wParam, lParam);
	}


	//CWindowImplBaseT
	void OnFinalMessage(::HWND hWnd) override
	{
		::UnhookWindowsHookEx(m_hWin32Hook);
		::PostQuitMessage(0);
	}

	//T
	::LRESULT OnCreate(::UINT uMsg, ::WPARAM wParam, ::LPARAM lParam, ::BOOL& bHandled)
	{
		m_ButtonAltF4 = ::CreateWindowExW(0U, L"Button", L"屏蔽Alt+F4", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 25, 20, 250, 20, this->m_hWnd, NULL, NULL, NULL);
		m_ButtonAltTab = ::CreateWindowExW(0U, L"Button", L"屏蔽Alt+Tab", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 25, 50, 250, 20, this->m_hWnd, NULL, NULL, NULL);
		m_ButtonLeftWin = ::CreateWindowExW(0U, L"Button", L"屏蔽左Win", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 25, 80, 250, 20, this->m_hWnd, NULL, NULL, NULL);
		HookInstance = this;
		m_hWin32Hook = ::SetWindowsHookExW(WH_KEYBOARD_LL, &LowLevelKeyboardProc, NULL, 0U);
		return TRUE;
	}

	//Message map
	BEGIN_MSG_MAP(CWindowImplWin32Hook)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
	END_MSG_MAP()	
};

CWindowImplWin32Hook * CWindowImplWin32Hook::HookInstance = NULL;


int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE ,LPWSTR lpCmdLine,int nCmdShow)
{
	::CWindowImplWin32Hook hWnd;

	::RECT rect = { 200, 100, 525, 270 };
	hWnd.Create(NULL, rect, L"Win32快捷键屏蔽工具", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	hWnd.ShowWindow(nCmdShow);

	::MSG msg;
	::GetMessageW(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
		::GetMessageW(&msg, NULL, 0, 0);
	}

	return static_cast<int>(msg.wParam);
}
