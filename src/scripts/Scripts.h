#ifndef CPP_PARENTAL_CONTROLLER_SHUTDOWNSCRIPT_H
#define CPP_PARENTAL_CONTROLLER_SHUTDOWNSCRIPT_H

#include <string>

void scriptHandler(const std::wstring &command);
bool addToStartup(const std::wstring& appName, const std::wstring& appPath);

#endif //CPP_PARENTAL_CONTROLLER_SHUTDOWNSCRIPT_H