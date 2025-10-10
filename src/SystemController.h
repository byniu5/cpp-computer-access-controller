#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#ifdef _WIN32
#include <windows.h>
#endif

class SystemController {
public:
    SystemController();
    ~SystemController();
    
    bool ShutdownSystem(int delaySeconds = 0);
    bool CancelShutdown();
    bool ShowWarning(const char* message, const char* title);
    
private:
    bool AcquireShutdownPrivilege();
};

#endif // SYSTEMCONTROLLER_H
