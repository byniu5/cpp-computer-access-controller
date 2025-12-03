#include "Notifications.h"
#include <iostream>
#include <shellapi.h>

#pragma comment(lib, "shell32.lib")

void showToastNotificationViaPowerShell(const wchar_t* title, const wchar_t* message) {
    std::wcout << L"\n=== Notification ===" << std::endl;
    
    // Get console window handle
    HWND hWnd = GetConsoleWindow();
    if (hWnd == NULL) {
        hWnd = GetDesktopWindow();
    }
    
    // Create notification data
    NOTIFYICONDATAW nid = {};
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hWnd;
    nid.uID = 1001;
    nid.uFlags = NIF_INFO | NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.uCallbackMessage = WM_APP + 1;
    nid.dwInfoFlags = NIIF_WARNING | NIIF_LARGE_ICON;
    nid.uTimeout = 10000; // Show for 10 seconds
    
    // Load icon (warning icon)
    nid.hIcon = LoadIconW(NULL, reinterpret_cast<LPCWSTR>(IDI_WARNING));
    
    // Copy title and message (with proper length limits)
    wcsncpy_s(nid.szInfoTitle, 64, title, _TRUNCATE);
    wcsncpy_s(nid.szInfo, 256, message, _TRUNCATE);
    wcsncpy_s(nid.szTip, 128, L"Parental Controller", _TRUNCATE);
    
    // Add the notification icon to system tray
    if (!Shell_NotifyIconW(NIM_ADD, &nid)) {
        std::wcerr << L"ERROR: Failed to add notification icon. Error: " << GetLastError() << std::endl;
        return;
    }
    
    std::wcout << L"Notification displayed!" << std::endl;
    
    // Keep notification visible for specified time
    Sleep(5000);
    
    // Remove the icon from system tray
    Shell_NotifyIconW(NIM_DELETE, &nid);
    
    std::wcout << L"=== Notification completed ===" << std::endl;
}


