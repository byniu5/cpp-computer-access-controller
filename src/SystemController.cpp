#include "SystemController.h"

SystemController::SystemController() {
}

SystemController::~SystemController() {
}

bool SystemController::AcquireShutdownPrivilege() {
#ifdef _WIN32
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    
    if (!OpenProcessToken(GetCurrentProcess(), 
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return false;
    }
    
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    
    if (GetLastError() != ERROR_SUCCESS) {
        CloseHandle(hToken);
        return false;
    }
    
    CloseHandle(hToken);
    return true;
#else
    return false;
#endif
}

bool SystemController::ShutdownSystem(int delaySeconds) {
#ifdef _WIN32
    if (!AcquireShutdownPrivilege()) {
        return false;
    }
    
    if (delaySeconds > 0) {
        // Use shutdown command with delay
        char cmd[256];
        sprintf_s(cmd, sizeof(cmd), "shutdown /s /t %d /c \"Computer access time has expired\"", delaySeconds);
        system(cmd);
        return true;
    } else {
        // Immediate shutdown
        return ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 
                           SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER);
    }
#else
    return false;
#endif
}

bool SystemController::CancelShutdown() {
#ifdef _WIN32
    system("shutdown /a");
    return true;
#else
    return false;
#endif
}

bool SystemController::ShowWarning(const char* message, const char* title) {
#ifdef _WIN32
    MessageBoxA(NULL, message, title, MB_OK | MB_ICONWARNING | MB_TOPMOST);
    return true;
#else
    return false;
#endif
}
