#include "src/scripts/Scripts.h"
#include "src/scripts/Notifications.h"
#include "src/timer/Timer.h"
#include "src/data/Data.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

int main() {

    std::string password = "";
    std::wstring currentPath = getExecutablePath();

    struct Data::DataStruct dataStruct = {};
    Data::getData(dataStruct);

    // If the function from Scripts.cpp found the actual path of the .exe file, add this .exe to the registry as a
    // startup application.
    if (!currentPath.empty()) {
        addToStartup(currentPath);
    }

    if (Timer::isAllowedTime(dataStruct.start, dataStruct.end)) {
        std::cout << "Access controller\nWrite password:" << std::endl;
        std::cin >> password;

        while (password != Data::getPassword(dataStruct)) {
            std::cout << "Wrong password" << std::endl;
            std::cin >> password;
        }
        if (password == Data::getPassword(dataStruct)) {
            std::string value;
            std::cout << "Welcome" << std::endl;
            do {
                std::cout << "If you want change the settings click 's'\nIf you want to disable program click 'q'" << std::endl;
                Data::showData(dataStruct);
                std::cin >> value;
                if (value == "s") {
                    Data::setData(dataStruct);
                    Data::getData(dataStruct);
                }
            } while (value != "q");
            return 0;
        }
    } else {
        scriptHandler(L"shutdown /s /t 60");
        std::this_thread::sleep_for(std::chrono::milliseconds(30000));
        showToastNotificationViaPowerShell(
        L"Shutdown warning",
        L"Log in outside of allowed hours! In 30 seconds your computer will shutdown."
        );
    }
    std::cin.get();
    return 0;
}
