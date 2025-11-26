#include "src/scripts/ShutdownScript.h"
#include "src/timer/Timer.h"
#include "src/data/Data.h"

#include <string>
#include <iostream>

int main() {

    std::string quit;

    while (quit != "q") {
    //system("powershell.exe -ExecutionPolicy Bypass -File script.ps1");
        script_handler();
        std::cout << Timer::isAllowedTime(1700, 2000);
        std::cin >> quit;
    }
    struct Data::DataStruct dataStruct;

    Data::setData(dataStruct);
    Data::getData(dataStruct);

    std::cout << "PASSWORD LEAK!!!:" << dataStruct.password;



    return 0;
}