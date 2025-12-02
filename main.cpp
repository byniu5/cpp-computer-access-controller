#include "src/scripts/Scripts.h"
#include "src/scripts/Notifications.h"
#include "src/timer/Timer.h"
#include "src/data/Data.h"

#include <string>
#include <iostream>

int main() {

    std::string password = "";

    struct Data::DataStruct dataStruct;
    Data::getData(dataStruct);
    // If Windows 11/10
    //addToStartup();

    if (Timer::isAllowedTime(dataStruct.start, dataStruct.end)) {
        std::cout << "Access controller\nWrite password:" << std::endl;
        std::cin >> password;

        while (password != dataStruct.password) {
            std::cout << "Wrong password" << std::endl;
            std::cin >> password;
        }
        if (password == dataStruct.password) {
            std::cout << "Welcome" << std::endl;
            std::cout << "If you want change the settings click 's'\nIf you want to disable program click 'q'" << std::endl;
            std::string value;
            std::cin >> value;
            if (value == "s") {
                Data::setData(dataStruct);
            } else if (value == "q") {}
            return 0;
        }
    } else {
        showToastNotificationViaPowerShell(
        L"Log in outside of allowed hours",
        L"Time restriction active! In 1 minute your computer will turn off."
        );
        //script_handler(L"shutdown /s /t 60");
    }
    return 0;
}
