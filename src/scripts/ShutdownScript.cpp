#include <iostream>
#include <windows.h>

void script_handler() {

    // Windows structures that hold information.
    STARTUPINFO si;
    PROCESS_INFORMATION pi;         //  Structure that will receive info about the created process.
    // Fill the structure with zeros.
    ZeroMemory(&si, sizeof(si));
    // Tells Windows the size of the structure.
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a PowerShell process
    wchar_t cmd[] = L"powershell.exe -Command \"Write-Host 'Hello World'\"";

    // Parameters 1. application name 2. The command to execute 3. Process security attributes 4. Thread security attributes 5.  Don't inherit handles from parent
    if (CreateProcessW(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, LPSTARTUPINFOW(&si), &pi)) {

        // Powershell pauses C++ program until its script completes.
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Once Powershell completed close the handles.
        // A handle is like a ticket or ID that Windows gives you to refer to a resource.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        std::cout << "PowerShell finished" << std::endl;
    } else {
        std::wcerr << L"Failed to start PowerShell. Error: " << GetLastError() << std::endl;
    }

}
