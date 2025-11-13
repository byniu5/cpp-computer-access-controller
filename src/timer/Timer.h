#ifndef CPP_PARENTAL_CONTROLLER_TIMER_H
#define CPP_PARENTAL_CONTROLLER_TIMER_H

class Timer {

public:
    Timer();
    ~Timer();

    // Getters
    static float getCurrentTimeFloat(); // Convert it for easy calculation.
    static bool isAllowedTime(float start, float end); // Check the time.

private:
    // Helper method.
    static void getCurrentTime(int& hour, int& min);

};

#endif //CPP_PARENTAL_CONTROLLER_TIMER_H