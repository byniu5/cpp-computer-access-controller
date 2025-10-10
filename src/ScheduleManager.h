#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <string>
#include <vector>
#include <ctime>

struct TimeSlot {
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
};

struct DaySchedule {
    int dayOfWeek; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    std::vector<TimeSlot> timeSlots;
    bool enabled;
};

class ScheduleManager {
public:
    ScheduleManager();
    ~ScheduleManager();
    
    bool LoadSchedule(const std::string& filename);
    bool SaveSchedule(const std::string& filename);
    
    void SetDaySchedule(int dayOfWeek, const std::vector<TimeSlot>& slots, bool enabled);
    DaySchedule GetDaySchedule(int dayOfWeek) const;
    
    bool IsTimeAllowed(int dayOfWeek, int hour, int minute) const;
    
    std::vector<DaySchedule>& GetAllSchedules() { return schedules; }
    const std::vector<DaySchedule>& GetAllSchedules() const { return schedules; }
    
private:
    std::vector<DaySchedule> schedules;
    std::string configFile;
    
    void InitializeDefaultSchedule();
};

#endif // SCHEDULEMANAGER_H
