#include "TimeChecker.h"
#include <ctime>

TimeChecker::TimeChecker(ScheduleManager* scheduleManager, SystemController* systemController)
    : scheduleManager(scheduleManager), 
      systemController(systemController),
      running(false),
      warningShown(false),
      warningTimeMinutes(5) {
}

TimeChecker::~TimeChecker() {
    Stop();
}

void TimeChecker::Start() {
    running = true;
    warningShown = false;
}

void TimeChecker::Stop() {
    running = false;
}

void TimeChecker::GetCurrentTime(int& dayOfWeek, int& hour, int& minute) {
    time_t now = time(nullptr);
    struct tm timeinfo;
    
#ifdef _WIN32
    localtime_s(&timeinfo, &now);
#else
    localtime_r(&now, &timeinfo);
#endif
    
    dayOfWeek = timeinfo.tm_wday;
    hour = timeinfo.tm_hour;
    minute = timeinfo.tm_min;
}

void TimeChecker::CheckCurrentTime() {
    if (!running) {
        return;
    }
    
    int dayOfWeek, hour, minute;
    GetCurrentTime(dayOfWeek, hour, minute);
    
    bool allowed = scheduleManager->IsTimeAllowed(dayOfWeek, hour, minute);
    
    if (!allowed) {
        if (!warningShown) {
            ShowTimeExpiredWarning();
            warningShown = true;
        }
        InitiateShutdown();
    } else {
        // Check if we're approaching the end of allowed time
        DaySchedule schedule = scheduleManager->GetDaySchedule(dayOfWeek);
        if (schedule.enabled) {
            int currentMinutes = hour * 60 + minute;
            
            for (const auto& slot : schedule.timeSlots) {
                int startMinutes = slot.startHour * 60 + slot.startMinute;
                int endMinutes = slot.endHour * 60 + slot.endMinute;
                
                // Check if we're currently in this time slot
                if (currentMinutes >= startMinutes && currentMinutes < endMinutes) {
                    int timeUntilEnd = endMinutes - currentMinutes;
                    
                    // Show warning if within warning time
                    if (timeUntilEnd > 0 && timeUntilEnd <= warningTimeMinutes && !warningShown) {
                        char message[256];
#ifdef _WIN32
                        sprintf_s(message, sizeof(message), "Warning: Computer access will end in %d minutes.", timeUntilEnd);
#else
                        snprintf(message, sizeof(message), "Warning: Computer access will end in %d minutes.", timeUntilEnd);
#endif
                        systemController->ShowWarning(message, "Access Time Warning");
                        warningShown = true;
                    } else if (timeUntilEnd > warningTimeMinutes) {
                        // Reset warning flag if we're not in warning period yet
                        warningShown = false;
                    }
                    break;
                }
            }
        }
    }
}

void TimeChecker::ShowTimeExpiredWarning() {
    systemController->ShowWarning(
        "Your computer access time has expired. The system will shutdown in 60 seconds.",
        "Access Time Expired"
    );
}

void TimeChecker::InitiateShutdown() {
    systemController->ShutdownSystem(60);
    Stop();
}
