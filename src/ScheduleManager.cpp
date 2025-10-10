#include "ScheduleManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

ScheduleManager::ScheduleManager() {
    InitializeDefaultSchedule();
}

ScheduleManager::~ScheduleManager() {
}

void ScheduleManager::InitializeDefaultSchedule() {
    schedules.clear();
    for (int i = 0; i < 7; i++) {
        DaySchedule day;
        day.dayOfWeek = i;
        day.enabled = true;
        
        // Default: Allow access from 8:00 AM to 8:00 PM
        TimeSlot defaultSlot;
        defaultSlot.startHour = 8;
        defaultSlot.startMinute = 0;
        defaultSlot.endHour = 20;
        defaultSlot.endMinute = 0;
        day.timeSlots.push_back(defaultSlot);
        
        schedules.push_back(day);
    }
}

bool ScheduleManager::LoadSchedule(const std::string& filename) {
    configFile = filename;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    schedules.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        int day, enabled, numSlots;
        if (!(iss >> day >> enabled >> numSlots)) continue;
        
        DaySchedule daySchedule;
        daySchedule.dayOfWeek = day;
        daySchedule.enabled = (enabled == 1);
        
        for (int i = 0; i < numSlots; i++) {
            TimeSlot slot;
            if (!(iss >> slot.startHour >> slot.startMinute >> slot.endHour >> slot.endMinute)) {
                break;
            }
            daySchedule.timeSlots.push_back(slot);
        }
        
        schedules.push_back(daySchedule);
    }
    
    file.close();
    
    // Ensure all days are present
    if (schedules.size() != 7) {
        InitializeDefaultSchedule();
        return false;
    }
    
    return true;
}

bool ScheduleManager::SaveSchedule(const std::string& filename) {
    configFile = filename;
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << "# Computer Access Schedule\n";
    file << "# Format: day enabled numSlots [startHour startMinute endHour endMinute]...\n";
    file << "# day: 0=Sunday, 1=Monday, ..., 6=Saturday\n\n";
    
    for (const auto& day : schedules) {
        file << day.dayOfWeek << " " << (day.enabled ? 1 : 0) << " " << day.timeSlots.size();
        for (const auto& slot : day.timeSlots) {
            file << " " << slot.startHour << " " << slot.startMinute 
                 << " " << slot.endHour << " " << slot.endMinute;
        }
        file << "\n";
    }
    
    file.close();
    return true;
}

void ScheduleManager::SetDaySchedule(int dayOfWeek, const std::vector<TimeSlot>& slots, bool enabled) {
    if (dayOfWeek < 0 || dayOfWeek >= 7) return;
    
    for (auto& day : schedules) {
        if (day.dayOfWeek == dayOfWeek) {
            day.timeSlots = slots;
            day.enabled = enabled;
            return;
        }
    }
}

DaySchedule ScheduleManager::GetDaySchedule(int dayOfWeek) const {
    for (const auto& day : schedules) {
        if (day.dayOfWeek == dayOfWeek) {
            return day;
        }
    }
    
    DaySchedule empty;
    empty.dayOfWeek = dayOfWeek;
    empty.enabled = false;
    return empty;
}

bool ScheduleManager::IsTimeAllowed(int dayOfWeek, int hour, int minute) const {
    DaySchedule day = GetDaySchedule(dayOfWeek);
    
    if (!day.enabled) {
        return false;
    }
    
    int currentMinutes = hour * 60 + minute;
    
    for (const auto& slot : day.timeSlots) {
        int startMinutes = slot.startHour * 60 + slot.startMinute;
        int endMinutes = slot.endHour * 60 + slot.endMinute;
        
        if (currentMinutes >= startMinutes && currentMinutes < endMinutes) {
            return true;
        }
    }
    
    return false;
}
