#ifndef TIMECHECKER_H
#define TIMECHECKER_H

#include "ScheduleManager.h"
#include "SystemController.h"
#include <wx/timer.h>

class TimeChecker {
public:
    TimeChecker(ScheduleManager* scheduleManager, SystemController* systemController);
    ~TimeChecker();
    
    void Start();
    void Stop();
    bool IsRunning() const { return running; }
    
    void CheckCurrentTime();
    
private:
    ScheduleManager* scheduleManager;
    SystemController* systemController;
    bool running;
    bool warningShown;
    int warningTimeMinutes;
    
    void GetCurrentTime(int& dayOfWeek, int& hour, int& minute);
    void ShowTimeExpiredWarning();
    void InitiateShutdown();
};

#endif // TIMECHECKER_H
