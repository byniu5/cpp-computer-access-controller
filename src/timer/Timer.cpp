#include "Timer.h"
#include <ctime>

Timer::Timer() = default;

Timer::~Timer() = default;

void Timer::getCurrentTime(int &hour, int &min) {
    // Returns the current calendar time as a time_t type.
    time_t now = time(nullptr);
    // Localtime converts time_t into a tm struct pointer with few addresses to a different component like hours, minutes, days.
    struct tm* localTime = localtime(&now);
    // Extracts the components from tm struct
    hour = localTime->tm_hour;
    min = localTime->tm_min;
}

float Timer::getCurrentTimeFloat() {
    int hour, min;
    getCurrentTime(hour, min);
    return hour * 100 + (min / 60.0f) * 100;
}

bool Timer::isAllowedTime(float start, float end) {
    float currentTime = getCurrentTimeFloat();
    return (currentTime >= start) && (currentTime <= end);
}