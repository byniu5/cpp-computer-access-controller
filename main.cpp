#include "src/scripts/Scripts.h"
#include "src/scripts/Notifications.h"
#include "src/timer/Timer.h"
#include "src/data/Data.h"

#include <string>
#include <iostream>

int main() {

    std::string quit;

    while (quit != "q") {
    //system("powershell.exe -ExecutionPolicy Bypass -File script.ps1");
        script_handler();
        showToastNotificationViaPowerShell(
        L"Parental Controller",
        L"Time restriction active! You have 5 minutes to log out or enter password."
        );
        std::cout << Timer::isAllowedTime(1700, 2000);
        std::cin >> quit;
    }
    struct Data::DataStruct dataStruct;

    Data::setData(dataStruct);
    Data::getData(dataStruct);

    std::cout << "PASSWORD LEAK!!!:" << dataStruct.password;

    return 0;
}