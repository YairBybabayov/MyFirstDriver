/* beep_driver.c */
#include<Windows.h>
#include<ntddbeep.h>
#include<stdio.h>
#include<winternl.h>

#pragma comment(lib, "ntdll")

int main() {
	HANDLE hDevice;
	UNICODE_STRING devName;
	RtlInitUnicodeString(&devName, DD_BEEP_DEVICE_NAME_U);
	OBJECT_ATTRIBUTES devAttr;
	InitializeObjectAttributes(&devAttr, &devName, 0, NULL, NULL);
	IO_STATUS_BLOCK ioStatus;
	NTSTATUS status = NtOpenFile(&hDevice, GENERIC_WRITE, &devAttr, &ioStatus, 0, 0);
	if (status == 0) {
		MessageBoxW(
			NULL,
			L"Get Ready For The Beep",
			L"driver test",
			MB_OKCANCEL | MB_ICONEXCLAMATION
		);
		//printf("Handle: 0x%p\n", hDevice);
		BEEP_SET_PARAMETERS note;
		note.Frequency = 800;
		note.Duration = 3000;
		DWORD ret;
		DeviceIoControl(hDevice, IOCTL_BEEP_SET, &note, sizeof(note), NULL, 0, &ret, NULL);
		CloseHandle(hDevice);
	}
	return 0;
}


