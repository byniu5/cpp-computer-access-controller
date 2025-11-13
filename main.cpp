#include <iostream>
#include "src/scripts/ShutdownScript.cpp"
#include <string>

int main() {

    std::string quit;

    while (quit != "q") {
    //system("powershell.exe -ExecutionPolicy Bypass -File script.ps1");
        script_handler();
        std::cin >> quit;
    }

    return 0;
}