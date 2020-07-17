
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

static bool _Internal_Hook_Tab = false;
static bool _Internal_Hook_6 = false;
static bool _Internal_Hook_Q = false;
static bool _Internal_Hook_W = false;
static bool _Internal_Hook_E = false;
static bool _Internal_Hook_R = false;
static bool _Internal_Hook_T = false;
static bool _Internal_Hook_1 = false;
static bool _Internal_Hook_2 = false;
static bool _Internal_Hook_3 = false;
static bool _Internal_Hook_4 = false;
static bool _Internal_Hook_5 = false;
static bool _Internal_Hook_A = false;
static bool _Internal_Hook_S = false;
static bool _Internal_Hook_D = false;
static bool _Internal_Hook_F = false;
static bool _Internal_Hook_G = false;

static bool _Internal_Hook_F1 = false;
static bool _Internal_Hook_F2 = false;
static bool _Internal_Hook_F3 = false;
static bool _Internal_Hook_F4 = false;

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

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& (pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

			{
				if (_Internal_Hook_AltF4)
				{
					return 1; //Hook Alt+F4
				}
			}
			//-DragonNest----------------------------------  
			else if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_F4)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_OEM_3;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_OEM_3;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = '4';
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = '4';
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_OEM_3;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_OEM_3;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'F4'
				}
			}
			else if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& (pKeyboardLowLevel->flags & LLKHF_UP)) //Being Released
			{
				if (_Internal_Hook_F4)
				{
					return 1; //Hook 'F4'
				}
			}
		}
		break;

		case VK_TAB:
		{
			assert(pKeyboardLowLevel->vkCode == VK_TAB);

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& (pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_AltTab)
				{
					return 1; //Hook Alt+Tab
				}
			}
			//-QQFO----------------------------------
			else if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_Tab)
				{
					return 1; //Hook Tab
				}
			}
		}
		break;

		case VK_LWIN:
		{
			assert(pKeyboardLowLevel->vkCode == VK_LWIN);

			if ((pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Extended Key
					//&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_LWin)
				{
					return 1; //Hook L-Win
				}
			}
		}
		break;

		case VK_ESCAPE:
		{
			assert(pKeyboardLowLevel->vkCode == VK_ESCAPE);

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
					// && !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_ESC)
				{
					return 1; //Hook ESC
				}
			}
		}
		break;

		//-QQFO----------------------------------	
		case '6':
		{
			assert(pKeyboardLowLevel->vkCode == '6');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

			{
				if (_Internal_Hook_6)
				{
					INPUT _inputs[2];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_F5;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_F5;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					UINT _res = SendInput(2, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook '6'
				}
			}
		}
		break;

		case 'Q':
		{
			assert(pKeyboardLowLevel->vkCode == 'Q');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

			{
				if (_Internal_Hook_Q)
				{
					INPUT _inputs[2];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_F6;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_F6;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					UINT _res = SendInput(2, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'Q'
				}
			}

		}
		break;

		case 'W':
		{
			assert(pKeyboardLowLevel->vkCode == 'W');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

			{
				if (_Internal_Hook_W)
				{
					INPUT _inputs[2];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_F7;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_F7;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					UINT _res = SendInput(2, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'W'
				}
			}

		}
		break;

		case 'E':
		{
			assert(pKeyboardLowLevel->vkCode == 'E');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

			{
				if (_Internal_Hook_E)
				{
					INPUT _inputs[2];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_F8;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_F8;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					UINT _res = SendInput(2, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'E'
				}
			}

		}
		break;

		case 'R':
		{
			assert(pKeyboardLowLevel->vkCode == 'R');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

			{
				if (_Internal_Hook_R)
				{
					INPUT _inputs[2];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_F9;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_F9;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					UINT _res = SendInput(2, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'R'
				}
			}

		}
		break;

		case 'T':
		{
			assert(pKeyboardLowLevel->vkCode == 'T');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed

			{
				if (_Internal_Hook_T)
				{
					INPUT _inputs[2];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_F10;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_F10;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					UINT _res = SendInput(2, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'T'
				}
			}

		}
		break;

		case '1':
		{
			assert(pKeyboardLowLevel->vkCode == '1');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_1)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F1;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F1;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook '1'
				}
			}
		}
		break;

		case '2':
		{
			assert(pKeyboardLowLevel->vkCode == '2');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_2)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F2;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F2;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook '2'
				}
			}
		}
		break;

		case '3':
		{
			assert(pKeyboardLowLevel->vkCode == '3');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_3)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F3;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F3;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook '3'
				}
			}
		}
		break;

		case '4':
		{
			assert(pKeyboardLowLevel->vkCode == '4');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_4)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F4;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F4;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook '4'
				}
			}
		}
		break;

		case '5':
		{
			assert(pKeyboardLowLevel->vkCode == '5');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_5)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F5;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F5;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook '5'
				}
			}
		}
		break;

		case 'A':
		{
			assert(pKeyboardLowLevel->vkCode == 'A');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_A)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F6;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F6;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'A'
				}
			}
		}
		break;

		case 'S':
		{
			assert(pKeyboardLowLevel->vkCode == 'S');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_S)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F7;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F7;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'S'
				}
			}
		}
		break;

		case 'D':
		{
			assert(pKeyboardLowLevel->vkCode == 'D');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_D)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F8;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F8;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'D'
				}
			}
		}
		break;

		case 'F':
		{
			assert(pKeyboardLowLevel->vkCode == 'F');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_F)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F9;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F9;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'F'
				}
			}
		}
		break;

		case 'G':
		{
			assert(pKeyboardLowLevel->vkCode == 'G');

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_G)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_TAB;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_TAB;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = VK_F10;
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = VK_F10;
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_TAB;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_TAB;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'G'
				}
			}
		}
		break;

		//-DragonNest----------------------------------  
		case VK_F1:
		{
			assert(pKeyboardLowLevel->vkCode == VK_F1);

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_F1)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_OEM_3;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_OEM_3;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = '1';
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = '1';
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_OEM_3;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_OEM_3;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'F1'
				}
			}
			else if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& (pKeyboardLowLevel->flags & LLKHF_UP)) //Being Released
			{
				if (_Internal_Hook_F1)
				{
					return 1; //Hook 'F1'
				}
			}
		}
		break;

		case VK_F2:
		{
			assert(pKeyboardLowLevel->vkCode == VK_F2);

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_F2)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_OEM_3;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_OEM_3;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = '2';
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = '2';
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_OEM_3;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_OEM_3;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'F2'
				}
			}
			else if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& (pKeyboardLowLevel->flags & LLKHF_UP)) //Being Released
			{
				if (_Internal_Hook_F2)
				{
					return 1; //Hook 'F2'
				}
			}
		}
		break;

		case VK_F3:
		{
			assert(pKeyboardLowLevel->vkCode == VK_F3);

			if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& !(pKeyboardLowLevel->flags & LLKHF_UP)) //Being Pressed
			{
				if (_Internal_Hook_F3)
				{
					INPUT _inputs[6];
					_inputs[0].type = INPUT_KEYBOARD;
					_inputs[0].ki.wVk = VK_OEM_3;
					_inputs[0].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[0].ki.dwFlags = 0;
					_inputs[0].ki.time = 0;
					_inputs[0].ki.dwExtraInfo = 0;
					_inputs[1].type = INPUT_KEYBOARD;
					_inputs[1].ki.wVk = VK_OEM_3;
					_inputs[1].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[1].ki.time = 0;
					_inputs[1].ki.dwExtraInfo = 0;
					_inputs[2].type = INPUT_KEYBOARD;
					_inputs[2].ki.wVk = '3';
					_inputs[2].ki.wScan = 0; //KEYEVENTF_SCANCODE		
					_inputs[2].ki.dwFlags = 0;
					_inputs[2].ki.time = 0;
					_inputs[2].ki.dwExtraInfo = 0;
					_inputs[3].type = INPUT_KEYBOARD;
					_inputs[3].ki.wVk = '3';
					_inputs[3].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[3].ki.time = 0;
					_inputs[3].ki.dwExtraInfo = 0;
					_inputs[4].type = INPUT_KEYBOARD;
					_inputs[4].ki.wVk = VK_OEM_3;
					_inputs[4].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[4].ki.dwFlags = 0;
					_inputs[4].ki.time = 0;
					_inputs[4].ki.dwExtraInfo = 0;
					_inputs[5].type = INPUT_KEYBOARD;
					_inputs[5].ki.wVk = VK_OEM_3;
					_inputs[5].ki.wScan = 0; //KEYEVENTF_SCANCODE  
					_inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
					_inputs[5].ki.time = 0;
					_inputs[5].ki.dwExtraInfo = 0;
					UINT _res = SendInput(6, _inputs, sizeof(INPUT));
					assert(_res != 0U);

					return 1; //Hook 'F3'
				}
			}
			else if (!(pKeyboardLowLevel->flags & LLKHF_EXTENDED) //Not Extended Key
				&& !(pKeyboardLowLevel->flags & LLKHF_INJECTED) //From the local keyboard driver //Not from calls to the keybd_event function
				&& !(pKeyboardLowLevel->flags & LLKHF_ALTDOWN) //ALT Key Not Pressed
				&& (pKeyboardLowLevel->flags & LLKHF_UP)) //Being Released
			{
				if (_Internal_Hook_F3)
				{
					return 1; //Hook 'F3'
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

		LRESULT _res5 = SendDlgItemMessageW(hWnd, IDC_TAB, BM_SETCHECK, (_Internal_Hook_Tab ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res5 == 0);
		LRESULT _res6 = SendDlgItemMessageW(hWnd, IDC_6, BM_SETCHECK, (_Internal_Hook_6 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res6 == 0);
		LRESULT _res7 = SendDlgItemMessageW(hWnd, IDC_Q, BM_SETCHECK, (_Internal_Hook_Q ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res7 == 0);
		LRESULT _res8 = SendDlgItemMessageW(hWnd, IDC_W, BM_SETCHECK, (_Internal_Hook_W ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res8 == 0);
		LRESULT _res9 = SendDlgItemMessageW(hWnd, IDC_E, BM_SETCHECK, (_Internal_Hook_E ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res9 == 0);
		LRESULT _res10 = SendDlgItemMessageW(hWnd, IDC_R, BM_SETCHECK, (_Internal_Hook_R ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res10 == 0);
		LRESULT _res11 = SendDlgItemMessageW(hWnd, IDC_T, BM_SETCHECK, (_Internal_Hook_T ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res11 == 0);
		LRESULT _res12 = SendDlgItemMessageW(hWnd, IDC_1, BM_SETCHECK, (_Internal_Hook_1 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res12 == 0);
		LRESULT _res13 = SendDlgItemMessageW(hWnd, IDC_2, BM_SETCHECK, (_Internal_Hook_2 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res13 == 0);
		LRESULT _res14 = SendDlgItemMessageW(hWnd, IDC_3, BM_SETCHECK, (_Internal_Hook_3 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res14 == 0);
		LRESULT _res15 = SendDlgItemMessageW(hWnd, IDC_4, BM_SETCHECK, (_Internal_Hook_4 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res15 == 0);
		LRESULT _res16 = SendDlgItemMessageW(hWnd, IDC_5, BM_SETCHECK, (_Internal_Hook_5 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res16 == 0);
		LRESULT _res17 = SendDlgItemMessageW(hWnd, IDC_A, BM_SETCHECK, (_Internal_Hook_A ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res17 == 0);
		LRESULT _res18 = SendDlgItemMessageW(hWnd, IDC_S, BM_SETCHECK, (_Internal_Hook_S ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res18 == 0);
		LRESULT _res19 = SendDlgItemMessageW(hWnd, IDC_D, BM_SETCHECK, (_Internal_Hook_D ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res19 == 0);
		LRESULT _res20 = SendDlgItemMessageW(hWnd, IDC_F, BM_SETCHECK, (_Internal_Hook_F ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res20 == 0);
		LRESULT _res21 = SendDlgItemMessageW(hWnd, IDC_G, BM_SETCHECK, (_Internal_Hook_G ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res21 == 0);

		LRESULT _res22 = SendDlgItemMessageW(hWnd, IDC_F1, BM_SETCHECK, (_Internal_Hook_F1 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res22 == 0);
		LRESULT _res23 = SendDlgItemMessageW(hWnd, IDC_F2, BM_SETCHECK, (_Internal_Hook_F2 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res23 == 0);
		LRESULT _res24 = SendDlgItemMessageW(hWnd, IDC_F3, BM_SETCHECK, (_Internal_Hook_F3 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res24 == 0);
		LRESULT _res25 = SendDlgItemMessageW(hWnd, IDC_F4, BM_SETCHECK, (_Internal_Hook_F4 ? BST_CHECKED : BST_UNCHECKED), 0);
		assert(_res25 == 0);

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

		case IDC_ENABLEQQFO:
		{
			LRESULT _res1 = SendDlgItemMessageW(hWnd, IDC_TAB, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res1 == 0);
			LRESULT _res2 = SendDlgItemMessageW(hWnd, IDC_6, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res2 == 0);
			LRESULT _res3 = SendDlgItemMessageW(hWnd, IDC_Q, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res3 == 0);
			LRESULT _res4 = SendDlgItemMessageW(hWnd, IDC_W, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res4 == 0);
			LRESULT _res5 = SendDlgItemMessageW(hWnd, IDC_E, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res5 == 0);
			LRESULT _res6 = SendDlgItemMessageW(hWnd, IDC_R, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res6 == 0);
			LRESULT _res7 = SendDlgItemMessageW(hWnd, IDC_T, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res7 == 0);
			LRESULT _res8 = SendDlgItemMessageW(hWnd, IDC_1, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res8 == 0);
			LRESULT _res9 = SendDlgItemMessageW(hWnd, IDC_2, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res9 == 0);
			LRESULT _res10 = SendDlgItemMessageW(hWnd, IDC_3, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res10 == 0);
			LRESULT _res11 = SendDlgItemMessageW(hWnd, IDC_4, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res11 == 0);
			LRESULT _res12 = SendDlgItemMessageW(hWnd, IDC_5, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res12 == 0);
			LRESULT _res13 = SendDlgItemMessageW(hWnd, IDC_A, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res13 == 0);
			LRESULT _res14 = SendDlgItemMessageW(hWnd, IDC_S, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res14 == 0);
			LRESULT _res15 = SendDlgItemMessageW(hWnd, IDC_D, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res15 == 0);
			LRESULT _res16 = SendDlgItemMessageW(hWnd, IDC_F, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res16 == 0);
			LRESULT _res17 = SendDlgItemMessageW(hWnd, IDC_G, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res17 == 0);

			_Internal_Hook_Tab = true;
			_Internal_Hook_6 = true;
			_Internal_Hook_Q = true;
			_Internal_Hook_W = true;
			_Internal_Hook_E = true;
			_Internal_Hook_R = true;
			_Internal_Hook_T = true;
			_Internal_Hook_1 = true;
			_Internal_Hook_2 = true;
			_Internal_Hook_3 = true;
			_Internal_Hook_4 = true;
			_Internal_Hook_5 = true;
			_Internal_Hook_A = true;
			_Internal_Hook_S = true;
			_Internal_Hook_D = true;
			_Internal_Hook_F = true;
			_Internal_Hook_G = true;
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_DISABLEQQFO:
		{
			LRESULT _res1 = SendDlgItemMessageW(hWnd, IDC_TAB, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res1 == 0);
			LRESULT _res2 = SendDlgItemMessageW(hWnd, IDC_6, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res2 == 0);
			LRESULT _res3 = SendDlgItemMessageW(hWnd, IDC_Q, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res3 == 0);
			LRESULT _res4 = SendDlgItemMessageW(hWnd, IDC_W, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res4 == 0);
			LRESULT _res5 = SendDlgItemMessageW(hWnd, IDC_E, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res5 == 0);
			LRESULT _res6 = SendDlgItemMessageW(hWnd, IDC_R, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res6 == 0);
			LRESULT _res7 = SendDlgItemMessageW(hWnd, IDC_T, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res7 == 0);
			LRESULT _res8 = SendDlgItemMessageW(hWnd, IDC_1, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res8 == 0);
			LRESULT _res9 = SendDlgItemMessageW(hWnd, IDC_2, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res9 == 0);
			LRESULT _res10 = SendDlgItemMessageW(hWnd, IDC_3, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res10 == 0);
			LRESULT _res11 = SendDlgItemMessageW(hWnd, IDC_4, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res11 == 0);
			LRESULT _res12 = SendDlgItemMessageW(hWnd, IDC_5, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res12 == 0);
			LRESULT _res13 = SendDlgItemMessageW(hWnd, IDC_A, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res13 == 0);
			LRESULT _res14 = SendDlgItemMessageW(hWnd, IDC_S, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res14 == 0);
			LRESULT _res15 = SendDlgItemMessageW(hWnd, IDC_D, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res15 == 0);
			LRESULT _res16 = SendDlgItemMessageW(hWnd, IDC_F, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res16 == 0);
			LRESULT _res17 = SendDlgItemMessageW(hWnd, IDC_G, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res17 == 0);

			_Internal_Hook_Tab = false;
			_Internal_Hook_6 = false;
			_Internal_Hook_Q = false;
			_Internal_Hook_W = false;
			_Internal_Hook_E = false;
			_Internal_Hook_R = false;
			_Internal_Hook_T = false;
			_Internal_Hook_1 = false;
			_Internal_Hook_2 = false;
			_Internal_Hook_3 = false;
			_Internal_Hook_4 = false;
			_Internal_Hook_5 = false;
			_Internal_Hook_A = false;
			_Internal_Hook_S = false;
			_Internal_Hook_D = false;
			_Internal_Hook_F = false;
			_Internal_Hook_G = false;
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_TAB:
		{
			_Internal_Hook_Tab = (SendDlgItemMessageW(hWnd, IDC_TAB, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_6:
		{
			_Internal_Hook_6 = (SendDlgItemMessageW(hWnd, IDC_6, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_Q:
		{
			_Internal_Hook_Q = (SendDlgItemMessageW(hWnd, IDC_Q, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;


		case IDC_W:
		{
			_Internal_Hook_W = (SendDlgItemMessageW(hWnd, IDC_W, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_E:
		{
			_Internal_Hook_E = (SendDlgItemMessageW(hWnd, IDC_E, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_R:
		{
			_Internal_Hook_R = (SendDlgItemMessageW(hWnd, IDC_R, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_T:
		{
			_Internal_Hook_T = (SendDlgItemMessageW(hWnd, IDC_T, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_1:
		{
			_Internal_Hook_1 = (SendDlgItemMessageW(hWnd, IDC_1, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_2:
		{
			_Internal_Hook_2 = (SendDlgItemMessageW(hWnd, IDC_2, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_3:
		{
			_Internal_Hook_3 = (SendDlgItemMessageW(hWnd, IDC_3, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_4:
		{
			_Internal_Hook_4 = (SendDlgItemMessageW(hWnd, IDC_4, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_5:
		{
			_Internal_Hook_5 = (SendDlgItemMessageW(hWnd, IDC_5, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_A:
		{
			_Internal_Hook_A = (SendDlgItemMessageW(hWnd, IDC_A, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;


		case IDC_S:
		{
			_Internal_Hook_S = (SendDlgItemMessageW(hWnd, IDC_S, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_D:
		{
			_Internal_Hook_D = (SendDlgItemMessageW(hWnd, IDC_D, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_F:
		{
			_Internal_Hook_F = (SendDlgItemMessageW(hWnd, IDC_F, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_G:
		{
			_Internal_Hook_G = (SendDlgItemMessageW(hWnd, IDC_G, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_ENABLEDRAGONEST:
		{
			LRESULT _res1 = SendDlgItemMessageW(hWnd, IDC_F1, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res1 == 0);
			LRESULT _res2 = SendDlgItemMessageW(hWnd, IDC_F2, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res2 == 0);
			LRESULT _res3 = SendDlgItemMessageW(hWnd, IDC_F3, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res3 == 0);
			LRESULT _res4 = SendDlgItemMessageW(hWnd, IDC_F4, BM_SETCHECK, BST_CHECKED, 0);
			assert(_res4 == 0);

			_Internal_Hook_F1 = true;
			_Internal_Hook_F2 = true;
			_Internal_Hook_F3 = true;
			_Internal_Hook_F4 = true;
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_DISABLEDRAGONEST:
		{
			LRESULT _res1 = SendDlgItemMessageW(hWnd, IDC_F1, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res1 == 0);
			LRESULT _res2 = SendDlgItemMessageW(hWnd, IDC_F2, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res2 == 0);
			LRESULT _res3 = SendDlgItemMessageW(hWnd, IDC_F3, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res3 == 0);
			LRESULT _res4 = SendDlgItemMessageW(hWnd, IDC_F4, BM_SETCHECK, BST_UNCHECKED, 0);
			assert(_res4 == 0);

			_Internal_Hook_F1 = false;
			_Internal_Hook_F2 = false;
			_Internal_Hook_F3 = false;
			_Internal_Hook_F4 = false;
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_F1:
		{
			_Internal_Hook_F1 = (SendDlgItemMessageW(hWnd, IDC_F1, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_F2:
		{
			_Internal_Hook_F2 = (SendDlgItemMessageW(hWnd, IDC_F2, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_F3:
		{
			_Internal_Hook_F3 = (SendDlgItemMessageW(hWnd, IDC_F3, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}
		SetWindowLongPtrW(hWnd, DWLP_MSGRESULT, 0);
		return TRUE;

		case IDC_F4:
		{
			_Internal_Hook_F4 = (SendDlgItemMessageW(hWnd, IDC_F4, BM_GETCHECK, 0, 0) == BST_CHECKED);
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

