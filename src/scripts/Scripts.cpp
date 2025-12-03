#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

void scriptHandler(const std::wstring &command) {
    // Windows structures that hold information.
    STARTUPINFO si;
    PROCESS_INFORMATION pi;         //  Structure that will receive info about the created process.
    // Fill the structure with zeros.
    ZeroMemory(&si, sizeof(si));
    // Tells Windows the size of the structure.
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a PowerShell process
    std::wstring powershellCmd = L"powershell.exe -Command \"" + command + L"\"";
    std::vector<wchar_t> cmdBuffer(powershellCmd.begin(), powershellCmd.end());
    cmdBuffer.push_back(0); // Null terminator

    // Parameters 1. application name 2. The command to execute 3. Process security attributes 4. Thread security attributes 5.  Don't inherit handles from parent
    if (CreateProcessW(NULL, cmdBuffer.data(), NULL, NULL, FALSE, 0, NULL, NULL, LPSTARTUPINFOW(&si), &pi)) {
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

bool addToStartup(const std::wstring& appPath) {
    HKEY hKey;
    const std::wstring appName = L"Access Controller";
    // The path to the standard location of the user startup programs.
    const wchar_t* regPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    
    // Open the registry key
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, regPath, 0, KEY_SET_VALUE, &hKey);

    // Check if the key was opened successfully.
    if (result != ERROR_SUCCESS) {
        std::wcerr << L"Failed to open registry key. Error: " << result << std::endl;
        return false;
    }

    // Creates/updates a registry value with the application name as the key.
    result = RegSetValueExW(hKey, appName.c_str(), 0, REG_SZ,
                           (BYTE*)appPath.c_str(),
                           (appPath.length() + 1) * sizeof(wchar_t));

    RegCloseKey(hKey);

    if (result != ERROR_SUCCESS) {
        std::wcerr << L"Failed to set registry value. Error: " << result << std::endl;
        return false;
    }

    std::wcout << L"Successfully added to startup: " << std::endl;
    return true;
}

// Helper function to get the current executable path (.exe file, where is installed on the user computer).
std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    // NULL retrieves the path of the executable file of the current process
    if (GetModuleFileNameW(NULL, buffer, MAX_PATH) != 0) {
        return std::wstring(buffer);
    }
    return L"";
}
