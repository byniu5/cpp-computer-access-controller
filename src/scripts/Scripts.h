#ifndef CPP_PARENTAL_CONTROLLER_SHUTDOWNSCRIPT_H
#define CPP_PARENTAL_CONTROLLER_SHUTDOWNSCRIPT_H

#include <string>

void script_handler();
bool addToStartup(const std::wstring& appName, const std::wstring& appPath);

#endif //CPP_PARENTAL_CONTROLLER_SHUTDOWNSCRIPT_H