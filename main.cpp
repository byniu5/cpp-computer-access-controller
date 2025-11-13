#include <iostream>
#include "src/scripts/ShutdownScript.h"
#include "src/timer/Timer.h"
#include <string>

int main() {

    std::string quit;

    while (quit != "q") {
    //system("powershell.exe -ExecutionPolicy Bypass -File script.ps1");
        script_handler();
        std::cout << Timer::isAllowedTime(1700, 2000);
        std::cin >> quit;
    }



    return 0;
}